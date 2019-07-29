#!/bin/bash

(export CLASSPATH=lib/:$CLASSPATH;java '-Djava.library.path=.:/usr/lib:lib' Synchro)
