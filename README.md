![Build status](https://travis-ci.org/ob-algdatii-ss18/leistungsnachweis-ride-distributor.svg?branch=master)

# Ride distributor

## Setup
### Create Workspace
```
cmake . -B".build" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug
```

### Create Executable (and documentation)
```
cmake --build .build --target all
cmake --build .build --target doc
```

### Unit Tests (first create executable)
```
cmake --build .build --target test
```
