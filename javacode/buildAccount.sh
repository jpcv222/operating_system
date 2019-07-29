#!/bin/bash
(export CLASSPATH=lib/:lib/libreadline-java.jar:$$CLASSPATH;javac -deprecation Account.java Semaphore.java Shared_memory.java)
