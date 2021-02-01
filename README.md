# LogAnalyser

This is an application that I implemented as a test task during the interviewing process in 2017. I rewrote it in 2021 to use it as a demo repository.

## Table of contents:
- [Problem statement](#problem-statement)
- [Input data description](#input-data-description)
- [Application requirements](#application-requirements)
- [Output requirements](#output-requirements)
- [Project structure](#project-structure)
- [Execution manual](#execution-manual)

## Problem statement

The game server produces logs in JSON format. The main goal is to parse the collection of logs and aggregate data in the requested style to the reporting file.

### Input data description
Any log file contains a lot of lines in JSON format. The JSON format describes user actions: 
```sh
{
	"ts_fact" : 1489494303,
	"fact_name": "fact1",
	"actor_id": 111222,
   
	"props":
	{
   	"prop1": 11,
   	"prop2": 22,
	…
   	"prop10": 1010,
	}
}
```
Description:
| Parameter | Description |
| ------ | ------ |
| ts_fact | The timestamp of an action |
| fact_name | The name of an action  |
| actor_id | The user Id that produced an action |
| props | Properties of an action: prop1...prop10 |


## Application requirements

- It must be running as a console application;
- It must be possible to analyze log files in multithreading mode;
- It must be possible to configure execution parameters via the command line:
  - The logs directory;
  - The number of files in the directory;
  - The number of threads running at the same time.


## Output requirements

The application must produce an output file: **arg.log**. It should contain the following data:
- For each **UTC+0**:
  - For each **fact_name**:
    - For each set of **props**:
      - The **total amount** of events found in logs.


## Project structure

### Stack
- C++17;
- MSVS 2019 (v142);
- [fmtlib/fmt](https://github.com/fmtlib/fmt);
- [tencent/rapidjson](https://github.com/Tencent/rapidjson).

### Solution ogranization 

The solution contains 3 projects:
- **LogAnalyserLib** - the library contains a collection of functional units:
  - CommandLineParser - parses command-line arguments set by a user;
  - ConsoleAppLogger - writes messages to the console. The wrapped is based on the **fmtlib/fmt**;
  - DataMerger - merges and calculated aggregated JSON data from all input files in an asynchronous way;
  - LogReader - reads each log file separately. It can be used in an asynchronous way. The JSON is parsed by means of **tencent/rapidjson**;
  - PlayerActionInfo - contains a collection of application data structures;
  - PlayerInfoAnalyser - analyses raw data grabbed from a single file;
  - ResultWriter - produces the output file and writes data to it.
- **LogAnalyserTests** - contains a collection of unit-tests to test the funcional uints of the LogAnalyserLib;
- **LogAnalyserBin** - contains a "glue-code" that implements the applictaion algorithm.


## Execution manual

The application can be executed via the command line:
```sh
> LogAnalyserBin.exe -d ..\\testFolder -n 10 -t 4
```
Description:
| Parameter | Description |
| ------ | ------ |
| -d | The directory with a collection of log files |
| -n | The number of files in the directory |
| -t | The number of active threads |

