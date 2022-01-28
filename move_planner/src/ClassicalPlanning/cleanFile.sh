#!/bin/bash

cat ClassicalPlanning/lp/clingoIstance.lp | sort | uniq > ClassicalPlanning/lp/clingoIn.lp
mv ClassicalPlanning/lp/clingoIn.lp ClassicalPlanning/lp/clingoIstance.lp
