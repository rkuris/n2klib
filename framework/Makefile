# This makefile updates json.hpp and inja.hpp from the latest
all: json.hpp inja.hpp
json.hpp:
	curl -LO $$(curl -s https://api.github.com/repos/nlohmann/json/releases/latest | jq -r '.assets[] | select (.browser_download_url | endswith("json.hpp")) | .browser_download_url')
inja.hpp:
	curl -LO https://raw.githubusercontent.com/pantor/inja/master/single_include/inja/inja.hpp

.PHONY: json.hpp inja.hpp all
