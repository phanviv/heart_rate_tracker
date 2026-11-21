# For This Iteration: Complete Implementation and Testing

In this iteration, your team will finish the implementation and test the whole system. Every stub from Iteration 3 is replaced with working code, every task is tested by a teammate, and every known bug is either fixed or recorded. By the end of the iteration, every menu option must work, and the program must compile without warnings and handle invalid input without crashing.

---

## 1. Assign a Project Leader

Choose one team member as Project Leader for this iteration. It should be someone who has not led before.

The Project Leader coordinates daily progress, makes sure every stub has an owner and a deadline, presents the status report at the check-in meeting, and keeps the task table and the test table up to date.

---

## 2. Complete Every Task

- Replace every remaining stub with working code. No menu option may print `"not implemented yet"` at the end of this iteration.
- Each member finishes their own tasks. If a task changes owner, record the change in the task table.
- Split the program into header and source files as planned in Iteration 3 (for example `account.h/.cpp`, `bank.h/.cpp`, `tasks.h/.cpp`, `main.cpp`).
- Check all user input: wrong types, negative numbers, values out of range, and items that do not exist.
- Commit your work to GitHub regularly with clear commit messages.

### Example: Task 4 (Transfer), from stub to working code

```cpp
void taskTransfer(Bank &bank)                 // T4, Student C: done
{
    cout << "From ";
    int from = readAccountIndex(bank);
    if (from == -1) return;

    cout << "To ";
    int to = readAccountIndex(bank);
    if (to == -1) return;

    if (from == to)
    {
        cout << "Cannot transfer to the same account" << endl;
        return;
    }

    cout << "Amount: ";
    long long cents = readCents();

    // All or nothing: deposit only if the withdrawal succeeded.
    if (bank.at(from).withdraw(cents))
    {
        bank.at(to).deposit(cents);
        cout << "Transfer done" << endl;
    }
    else
        cout << "Transfer refused" << endl;
}
```

---

## 3. Test the System

- Write a test table that covers every task. Include at least one normal case and one invalid or edge case for each task.
- **Cross-testing:** each member tests at least one task written by another member and records the result.
- Test the tasks together as well, for example: open two accounts, deposit, transfer, then list all accounts.
- For each failed test, open a GitHub Issue, fix the bug, and run the test again.

### Example test table (bank system)

| Test ID | Task            | Input                 | Expected result                       | Actual result         | Pass/Fail    | Tester    |
| ------- | --------------- | --------------------- | ------------------------------------- | --------------------- | ------------ | --------- |
| TC1     | T1 Open account | name "Maya Chen"      | account 1001 created                  | account 1001 created  | Pass         | Student B |
| TC2     | T2 Deposit      | account 1001, $250.75 | balance $250.75                       | balance $250.75       | Pass         | Student C |
| TC3     | T2 Deposit      | account 1001, -$10    | "Deposit refused"                     | "Deposit refused"     | Pass         | Student C |
| TC4     | T3 Withdraw     | account 1001, $1000   | "Withdrawal refused" (overdraft)      | balance went negative | Fail → fixed | Student D |
| TC5     | T4 Transfer     | 1001 → 1001, $10      | "Cannot transfer to the same account" | as expected           | Pass         | Student A |
| TC6     | T4 Transfer     | 1001 → 9999, $10      | "No account 9999", balances unchanged | as expected           | Pass         | Student A |
| TC7     | Menu            | letters "abc"         | "Invalid option", menu shown again    | as expected           | Pass         | Student B |

---

## 4. Improve Code Quality

- The program compiles with `-Wall -Wextra` and no warnings.
- Data members are private. Classes are used through their public methods only.
- Every file has a short header comment. Every function has a one-line comment that names the task and its owner.
- Names are clear and consistent. Remove unused code and debugging output.
- Before merging, at least one teammate reviews each member's code.

---

## 5. Follow the Iteration Schedule

| Date                  | Activity                 | What your team does                                                                                                                                                            |
| --------------------- | ------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Saturday, November 7  | Iteration starts         | Assign the Project Leader. List every remaining stub, its owner and its deadline. Start the test table.                                                                        |
| Tuesday, November 10  | Check-in meeting         | The Project Leader presents the task table and test results so far. Discuss bugs and blocked tasks, and reassign work if needed. Record notes and action items.                |
| Thursday, November 12 | Peer review and feedback | Demo the complete program to another team. Let them try invalid inputs. Exchange feedback on correctness, usability and code quality. Summarize the feedback and your changes. |
| Sunday, November 15   | Iteration deadline       | Every menu option works. All tests are run and recorded. Open bugs are listed as GitHub Issues. The final code is on GitHub.                                                   |

---

## 6. Document Your Progress

Work together to prepare one report in **Overleaf** and export it as a PDF. It must include:

- the final task table, with every task marked done (or explained if not)
- the updated system design: classes, menu, file structure and class diagram, with any changes since Iteration 3 explained
- the test table with results, and the list of bugs found and fixed
- sample program output for each menu option
- known limitations and remaining issues
- a summary of the check-in meeting and the peer feedback
- a leadership summary: who led and what they coordinated
- a contribution table showing what each student implemented, tested and reviewed during this iteration, and their tasks for the next iteration

Also update your **Project Plan (Excel)** with the final task table, the test table, the revised timeline, and each member's contributions.

### Your GitHub repository must contain:

- the complete source code, split into header and source files
- an updated `README` with build and run instructions and a short example of how to use the program
- a `docs/` folder with the PDF report and the Excel plan
- GitHub Issues for the bugs found during testing

> Each student must submit their own copy of the GitHub repository link on **Canvas**.

---

## 7. Teamwork and Individual Contributions

Your teamwork will be evaluated using the course rubric, which emphasizes collaboration, shared leadership, setting goals, planning tasks, and meeting objectives.

Each student will be evaluated on their ability to:

- **Take responsibility:** Finish your own tasks and fix the bugs found in them.
- **Collaborate respectfully:** Test and review teammates' code, give useful feedback, and help when someone is stuck.
- **Establish goals:** Help define test cases that show each task works.
- **Plan tasks:** Help keep the remaining work divided fairly and on schedule.
- **Meet objectives:** Deliver working, tested code on time and report problems early.

Each area will be rated on the following scale:

| Score | Meaning                      |
| ----- | ---------------------------- |
| 4     | Exceeds expectations         |
| 3     | Meets expectations           |
| 2     | Partially meets expectations |
| 1     | Does not meet expectations   |

Each student must also submit a brief **individual reflection** describing the tasks they completed and tested, how they supported the team, and one area for improvement. You will also complete a **confidential peer evaluation** of your teammates' participation and contributions.

Your individual evaluation will reflect your own contributions. It will be supported by the project documentation, GitHub activity, your reflection, peer feedback and instructor observations. The number of GitHub commits alone will not determine your evaluation.
