# This makefile updates all third-party single-file dependencies
all: json.hpp inja.hpp CLI11.hpp
json.hpp:
	curl -LO $$(curl -s https://api.github.com/repos/nlohmann/json/releases/latest | jq -r '.assets[] | select (.browser_download_url | endswith(".hpp")) | .browser_download_url')
inja.hpp:
	curl -LO https://raw.githubusercontent.com/pantor/inja/master/single_include/inja/inja.hpp

CLI11.hpp:
	curl -LO $$(curl -s https://api.github.com/repos/CLIUtils/CLI11/releases/latest | jq -r '.assets[] | select (.browser_download_url | endswith(".hpp")) | .browser_download_url')

.PHONY: json.hpp inja.hpp CLI11.hpp all
