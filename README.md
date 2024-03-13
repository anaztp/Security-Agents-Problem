# Security Agents Working Shifts Problem


# About The Problem
This problem has been adapted from a competition organized by the faculty of science at my university.

It serves as an excellent opportunity to explore a new programming language, as it encompasses various fundamental aspects of programming, such as:
- Input/output interactions
- Control flow mechanisms
- Handling data structures
- Understanding syntax and semantics
- Grasping the type system, if applicable
- And more...
Feel free to tackle this problem or enhance an existing solution in your language of choice and submit a pull request.

To access solutions, navigate to the "solutions" directory, where you'll find subdirectories labeled with the programming languages used for each solution. Detailed instructions on how to run each solution can be found within their respective directories.

Happy coding!

# The Problem
At the Faculty of Sciences, there are 20 security agents numbered from 1 to 20.

Out of these, 3 agents work during the night shift, while 5 agents work during the day.

For an agent working a night shift, there's a rule that they won't work for the following 2 days and 2 nights. For instance, if an agent works on Sunday night, they won't work all day on Monday and Tuesday, returning to work on Wednesday.

Similarly, an agent working during the day won't be assigned to the night shift on the same day. For instance, if an agent worked during the day on Sunday, they won't work the night shift on Sunday.

Your task is to create a schedule for each night and day until completing a cycle, ensuring all agents work an equal number of shifts, whether during the day or night.

The duration of the cycle isn't specified; it can span days, months, or any period you determine.

