SHELL := /usr/bin/env bash

create:
	@echo starting uC project creator
	bash ./scripts/create-project/create-project.sh

.PHONY: create