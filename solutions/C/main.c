#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define true 1
#define false 0

typedef enum { DAYLIGHT, NIGHT } Daytime;
typedef unsigned u32;
typedef char bool;
typedef struct Agent Agent;
typedef struct Agents Agents;
typedef struct Shift Shift;
typedef struct Day Day;
typedef struct Days Days;

struct Agent {
  u32 agent_id;
  u32 shifts_count;
  Shift *last_shift;
  u32 last_day;
};

struct Agents {
  Agent *list;
  u32 size;
};

struct Shift {
  Agent *agents[5];
  u32 capacity;
  Daytime daytime;
};

struct Day {
  Shift night_shift;
  Shift daylight_shift;
  u32 day;
};

struct Days {
  Day *list;
  u32 capacity;
  u32 size;
};

bool can_agent_work(Agent *agent, u32 current_day);
Agent *select_agent(Agents agents);
void fill_shift(Shift *shift, u32 current_day, Agents agents);
void fill_day(Day *day, Agents agents);
bool check_agents_distribution(Agents agents);
Days create_days(u32 capacity);
void free_days(Days days);
void append_days(Days *days, Day day);

int main() {
  Agents agents;
  agents.size = 1000;
  agents.list = malloc(agents.size * sizeof(Agent));
  for (u32 agent_id = 0; agent_id < agents.size; agent_id++) {
    agents.list[agent_id].agent_id = agent_id;
    agents.list[agent_id].last_day = -1;
    agents.list[agent_id].last_shift = NULL;
    agents.list[agent_id].shifts_count = 0;
  }
  Days days = create_days(10);
  // u32 guard = 0;
  for (u32 current_day = 0; /* guard < 1 */; current_day++) {
    append_days(&days, (Day){.day = current_day});
    fill_day(days.list + days.size - 1, agents);
    printf("Day %u\n", current_day);
    printf("  Night Shift: ");
    for (u32 i = 0; i < 3; i++) {
      printf("%u ", days.list[current_day].night_shift.agents[i]->agent_id);
    }
    printf("\n");
    printf("  Daylight Shift: ");
    for (u32 i = 0; i < 5; i++) {
      printf("%u ", days.list[current_day].daylight_shift.agents[i]->agent_id);
    }
    printf("\n");
    // guard++;
    if (check_agents_distribution(agents))
      return 0;
  }
  free_days(days);
  return 0;
}

bool can_agent_work(Agent *agent, u32 current_day) {
  assert((agent != NULL) && "invalid agent (pointer to agent is NULL)");
  if (agent->last_shift == NULL)
    return true;
  u32 no_work_days = current_day - agent->last_day;
  return (agent->last_shift->daytime == DAYLIGHT) ? (no_work_days > 0)
                                                  : (no_work_days > 2);
}

Agent *select_agent(Agents agents) {
  Agent *selected_agent = agents.list;
  for (u32 agent_id = 1; agent_id < agents.size; agent_id++) {
    if (selected_agent->shifts_count > agents.list[agent_id].shifts_count)
      selected_agent = agents.list + agent_id;
  }
  return selected_agent;
}

void fill_shift(Shift *shift, u32 current_day, Agents agents) {
  for (u32 agent_count = 0; agent_count < shift->capacity; agent_count++) {
    Agent *selected_agent = select_agent(agents);
    selected_agent->shifts_count++;
    shift->agents[agent_count] = selected_agent;
  }
}

void fill_day(Day *day, Agents agents) {
  day->night_shift.daytime = NIGHT;
  day->night_shift.capacity = 3;
  fill_shift(&(day->night_shift), day->day, agents);

  day->daylight_shift.daytime = DAYLIGHT;
  day->daylight_shift.capacity = 5;
  fill_shift(&(day->daylight_shift), day->day, agents);
}

bool check_agents_distribution(Agents agents) {
  Agent *selected_agent = select_agent(agents);
  return selected_agent == agents.list;
}

Days create_days(u32 capacity) {
  assert(capacity != 0 && "The capacity of is 0");
  return (Days){.list = (Day *)malloc(capacity * sizeof(Day)),
                .capacity = capacity,
                .size = 0};
}

void free_days(Days days) { free(days.list); }

void append_days(Days *days, Day day) {
  if (days->capacity == days->size) {
    days->capacity *= 2;
    assert(days->capacity != 0 && "The capacity of is 0");
    days->list = (Day *)realloc(days->list, days->capacity * sizeof(Day));
  }
  days->list[days->size] = day;
  days->size++;
}
