# E-Wallet Management System

A modular C++17 command-line wallet application with persistent storage, transaction history, and automated test coverage. The repository is structured to build cleanly and present well on GitHub.

## Highlights

- Persistent wallet accounts with file-backed storage
- User registration with email validation
- Deposit, withdrawal, and transfer workflows
- Transaction history persisted across runs
- CMake-based build and test integration
- GitHub Actions CI for automated verification

## Project Structure

```text
.
├── include/      # Public headers
├── src/          # Application and service implementation
├── tests/        # Executable test suite
├── data/         # Runtime data files
└── .github/      # CI workflow
```

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/ewallet
```

By default, runtime data is stored in `./data`.

## Test

```bash
ctest --test-dir build --output-on-failure
```

## Supported Operations

- Register user accounts
- Add wallet funds
- Withdraw available balance
- Transfer funds between users
- View balances
- List registered users
- Inspect transaction history

## GitHub Readiness

- Portable CMake configuration
- Separate reusable core target
- Automated test target
- CI workflow for Linux builds
- Improved repository hygiene with `.gitignore`

## Next Iterations

- JSON or SQLite persistence
- Authentication and authorization
- Currency conversion support
- REST API or web frontend
