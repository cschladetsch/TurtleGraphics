#!/bin/sh

lint Source/*.cpp
lint Source/Turtle/*.cpp
lint Include/Processor/*.hpp
lint Include/Turtle/{Display,Config,Position,Turtle,StdAliases}.hpp

