#!/bin/bash
scriptPath=${0%/*}
cd "$scriptPath"

./webservice -p 8080
