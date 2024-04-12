package main

import "fmt"

type Period uint

const (
	NOTHING Period = iota
	DAYTIME
	NIGHT
)

type Days []Day

type Agent struct {
	agentId   uint
	lastShift struct {
		period Period
		day    uint
	}
	shiftsCount uint
}

func (agent Agent) CanWork(currentDay uint) bool {
	diff := currentDay - agent.lastShift.day
	return (agent.lastShift.period == NIGHT && diff > 2) || (agent.lastShift.period == DAYTIME && diff > 0) || (agent.lastShift.period == NOTHING)
}

type Day struct {
	day   uint
	shift struct {
		daytime []*Agent
		night   []*Agent
	}
}

func (days *Days) Add(day Day) {
	if cap(*days) == len(*days) {
		temp := make(Days, cap(*days)+10)
		copy(temp, *days)
		*days = temp
	}
	*days = append(*days, day)
}

func SelectAgent(agents []Agent, currentDay uint) *Agent {
	var selected *Agent
	for i := 0; i < len(agents); i++ {
		if agents[i].CanWork(currentDay) && (selected == nil || agents[i].shiftsCount < selected.shiftsCount) {
			selected = &agents[i]
		}
	}
	return selected
}

func AreAgentsEqual(agents []Agent) bool {
	var shifts uint = agents[0].shiftsCount
	for i := 1; i < len(agents[1:]); i++ {
		if agents[i].shiftsCount != shifts {
			return false
		}
	}
	return true
}

func (day *Day) Fill(agents []Agent) {
	day.shift.daytime = make([]*Agent, 5)
	for i := 0; i < 5; i++ {
		selected := SelectAgent(agents, day.day)
		day.shift.daytime[i] = selected
		selected.lastShift.day = day.day
		selected.lastShift.period = DAYTIME
		selected.shiftsCount++
	}
	day.shift.night = make([]*Agent, 3)
	for i := 0; i < 3; i++ {
		selected := SelectAgent(agents, day.day)
		day.shift.night[i] = selected
		selected.lastShift.day = day.day
		selected.lastShift.period = NIGHT
		selected.shiftsCount++
	}
}

func main() {
	var agents = make([]Agent, 20)
	for i := uint(0); i < uint(len(agents)); i++ {
		agents[i].agentId = i
	}

	days := Days{}
	guard := 0
	for day := uint(0); guard < 10; day++ {
		currentDay := Day{
			day: day,
		}
		currentDay.Fill(agents)
		fmt.Printf("Day %d \n", day+1)
		fmt.Printf("	Daytime:")
		for _, agent := range currentDay.shift.daytime {
			fmt.Printf(" %d", agent.agentId)
		}
		fmt.Println()
		fmt.Printf("	Night:")
		for _, agent := range currentDay.shift.night {
			fmt.Printf(" %d", agent.agentId)
		}
		fmt.Println()
		days.Add(currentDay)
		if AreAgentsEqual(agents[:]) {
			fmt.Println("Done !")
			return
		}
		guard++
	}

}
