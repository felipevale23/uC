SHELL := /usr/bin/env bash

create:
	@echo starting uC project creator
	bash ./scripts/create-project/create-project.sh

install:
	@echo starting the installer
	bash ./scripts/xc8-installer/xc8_compiler_installer.sh

.PHONY: create install
