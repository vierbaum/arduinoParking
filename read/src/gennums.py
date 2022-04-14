#!/usr/bin/env python3

file = open("fakeInputs", "w")
while True:
    for i in range(255):
        file.write(str(i) + "\n")
