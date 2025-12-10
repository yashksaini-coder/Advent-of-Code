import re

from pulp import LpMinimize, LpProblem, LpVariable, lpSum


def solve_part1_machine(buttons, target_lights):
    """
    Solve Part 1: Find minimum button presses to configure indicator lights.
    Uses BFS/DP approach with bitmask to represent light states.
    """
    from collections import deque

    # Convert target string to bitmask
    target = 0
    for i, light in enumerate(target_lights):
        if light == "#":
            target |= 1 << i

    # BFS to find minimum presses
    queue = deque([(0, 0)])  # (current_state, presses)
    visited = {0}

    while queue:
        state, presses = queue.popleft()

        if state == target:
            return presses

        # Try pressing each button
        for button in buttons:
            next_state = state
            for light_idx in button:
                next_state ^= 1 << light_idx

            if next_state not in visited:
                visited.add(next_state)
                queue.append((next_state, presses + 1))

    return 0  # No solution found


def solve_part2_machine(buttons, joltages):
    """
    Solve Part 2: Find minimum button presses to reach joltage requirements.
    Uses Linear Programming to find optimal solution.
    """
    if not buttons or not joltages:
        return 0

    # Create LP problem
    prob = LpProblem("Machine_Problem", LpMinimize)

    # Create variables: x_i = number of times button i is pressed
    variables = [
        LpVariable(f"x_{i}", lowBound=0, cat="Integer") for i in range(len(buttons))
    ]

    # Objective: minimize total button presses
    prob += lpSum(variables), "Total_Presses"

    # Constraints: for each counter, sum of button presses must equal joltage
    for counter_idx in range(len(joltages)):
        # Find which buttons affect this counter
        affecting_buttons = []
        for btn_idx in range(len(buttons)):
            if counter_idx in buttons[btn_idx]:
                affecting_buttons.append(variables[btn_idx])

        # Add constraint: sum of affecting buttons = target joltage
        if affecting_buttons:
            prob += (
                lpSum(affecting_buttons) == joltages[counter_idx],
                f"Counter_{counter_idx}",
            )

    # Solve
    prob.solve()

    # Get total presses
    total = 0
    for var in variables:
        if var.varValue is not None:
            total += int(var.varValue)

    return total


def parse_line(line):
    """Parse a single line to extract lights, buttons, and joltages."""
    parts = line.strip().split()

    # Parse indicator lights [.##.]
    lights_str = parts[0][1:-1]  # Remove [ and ]

    # Parse buttons (0,1,2)
    button_matches = re.findall(r"\(([^)]+)\)", line)
    buttons = [list(map(int, b.split(","))) for b in button_matches]

    # Parse joltages {3,5,4,7}
    joltage_match = re.search(r"\{([^}]+)\}", line)
    joltages = (
        list(map(int, joltage_match.group(1).split(","))) if joltage_match else []
    )

    return lights_str, buttons, joltages


def main():
    part1_total = 0
    part2_total = 0

    with open("input.txt", "r") as f:
        for line in f:
            if line.strip():
                lights, buttons, joltages = parse_line(line)

                # Solve Part 1
                part1_total += solve_part1_machine(buttons, lights)

                # Solve Part 2
                part2_total += solve_part2_machine(buttons, joltages)

    print(f"Part 1: {part1_total}")
    print(f"Part 2: {part2_total}")


if __name__ == "__main__":
    main()
