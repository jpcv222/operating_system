#!/bin/bash
(export CLASSPATH=lib/:lib/libreadline-java.jar:$$CLASSPATH;javac -deprecation Synchro.java Semaphore.java)
