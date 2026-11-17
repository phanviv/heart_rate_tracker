# Project Workflow Guide

## The Big Picture

```
 main ──●───────────────●──>   (shared code, always working)
         \             /
          ●──●──●──●──●        (your branch for one issue)
```

1. **Pick an issue** from the GitHub Project and assign it to yourself.
2. **Create a branch** from `main`.
3. **Make changes** and save them with `add`, `commit`, and `push`.
4. **Open a pull request** (PR) on GitHub.
5. After review, it gets **merged into `main`**.

### Key Terms

- **`main`**: the official version of the project. Don't commit to it directly.
- **Branch**: your own copy of the code to work on without affecting others.
- **Issue**: a task, bug, or feature written up on GitHub.
- **Commit**: a saved snapshot of your changes.
- **Push / Pull**: upload your commits to GitHub / download the latest changes.
- **Pull Request (PR)**: a request to merge your branch into `main`.

---

## Step 1: Pick an Issue

1. Open the **Projects** tab on our [GitHub repo](https://github.com/phanviv/heart_rate_tracker).
2. Choose an issue nobody has taken, and under **Assignees** click **assign yourself**.
3. Note the issue number (for example, `#7`).

## Step 2: Create a Branch

Start from the latest `main`:

```bash
git switch main                       # go to main
git pull                              # get the latest changes
git switch -c user-profile   		  # create and switch to your branch
```

Use a short, descriptive branch name, like `iteration02/user-profile` or `fix/sensor-crash`.

## Step 3: Make and Save Changes

Edit your code, then repeat this loop as you go:

```bash
git status                     # see what you've changed (always safe to run)
git add .                      # stage all changes (or: git add main.cpp)
git commit -m "Add age input"  # save a snapshot with a short message
git push                       # upload to GitHub
```

The **first** time you push a new branch, use `git push -u origin <branch-name>`. After that, `git push` is enough.

**Tip:** commit small pieces often. Small commits are easier to review and easier to undo.

To bring the newest `main` into your branch:

```bash
git switch main
git pull
git switch user-profile
git merge main
```

## Step 4: Open a Pull Request

1. On GitHub, click **Compare & pull request** in the yellow banner, or go to **Pull requests** and then **New pull request**.
2. Set **base:** `main` and **compare:** your branch.
3. Add a clear title and a short description of what you changed.
4. Link the issue by writing `Closes #7` in the description. The issue closes automatically when the PR is merged.
5. Add a teammate as a **Reviewer**, then click **Create pull request**.

## Step 5: Review and Merge

- If your reviewer asks for changes, fix them on the **same branch** and push again. The PR updates automatically.
- Once it's approved, click **Merge pull request** and delete the branch.
- Then go back to `main` and update it:

  ```bash
  git switch main
  git pull
  ```

You're ready for the next issue!

---

## Cheat Sheet

| I want to...              | Command                   |
| ------------------------- | ------------------------- |
| See what's changed        | `git status`              |
| See which branch I'm on   | `git branch`              |
| Switch branches           | `git switch <branch>`     |
| Create a new branch       | `git switch -c <branch>`  |
| Stage all changes         | `git add .`               |
| Commit                    | `git commit -m "message"` |
| Upload / download changes | `git push` / `git pull`   |
| See past commits          | `git log --oneline`       |

## Common Mistakes

- **Working on `main` by accident.** Check with `git branch`. If you haven't committed yet, run `git switch -c <new-branch>` and your changes come with you.
- **Forgetting to pull first.** Always run `git pull` on `main` before creating a branch.
- **Merge conflicts.** These happen when two people change the same lines. Git marks the clash with `<<<<<<<`, `=======`, and `>>>>>>>`. Keep the code you want, delete the markers, then `add` and `commit`. If you're stuck, ask a teammate!

# Heart Rate Tracker

A C++ console program that tracks heart rate during workouts. Several profiles can be created and managed, each with its own settings and workout history. Readings are taken automatically (simulated for now), checked for alerts live, and saved automatically, with a backup file for crash recovery.

Team: Vivian and Kai

## Build and run

Requires a C++ compiler (g++ with C++11 or newer).

```
g++ -std=c++11 *.cpp -o hrtracker
./hrtracker
```

On Windows (MinGW):

```
g++ -std=c++11 *.cpp -o hrtracker.exe
hrtracker.exe
```

## Menu

```
1  Manage profiles (create, switch, rename, delete)
2  Start workout
3  View latest readings
4  Load data
5  View workout history
6  Statistics
7  Heart rate zones
8  Alerts
0  Exit
```

Data loads automatically at start-up and saves automatically after every workout and profile change. If a workout was interrupted, the program offers to continue it, save it as finished, or discard it.

## Data files (created when the program runs)

- `heart_data.txt`: profiles, workouts, and readings
- `settings.txt`: default and per-profile settings
- `workout_backup.txt`: the workout in progress (deleted when it ends)

## Project layout

- `main.cpp`, `tasks.h`, `tasks_data.cpp`, `tasks_analysis.cpp`: menu and task functions
- One `.h`/`.cpp` pair per class: `User` (UserProfile), `readings` (Reading), `readingl` (ReadingLog), `workout`, `settings`, `profilemanager`, `Sensor`, `alert`, `Filemanager`

## Docs

See the `docs/` folder:

- `Iteration_3_Report.pdf`: task table, design, class diagram, status
- `Iteration_3_Project_Plan.xlsx`: revised project plan
