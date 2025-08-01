all: prepare

install_min:
	sudo apt-get install gcc g++ cmake make doxygen

install_tests: install_min
	sudo apt-get install gcovr lcov

install: install_min install_tests
	sudo apt-get install git llvm pkg-config curl zip unzip tar python3-dev clang-format clang-tidy

install_pip:
	pip install jinja2 Pygments cmake-format pre-commit

install_doc: install_min
	sudo apt-get install doxygen
	pip install jinja2 Pygments

prepare:
	rm -rf build
	mkdir build

dependency_graph:
	cd build && cmake .. --graphviz=graph.dot && dot -Tpng graph.dot -o graphImage.png

git_submodule:
	git submodule update --init --recursive

git_submodule_add:
	git submodule add <github module url> <module name>

doxy_documentation:
	doxygen -g

doxygen_document_generate:
	cd docs && doxygen


clang_tidy_install:
	sudo apt-get install clang-tidy


cmake_format_install:
	pip3 install cmake-format

install_graphviz:
	sudo apt-get install graphviz

install_pre_commit:
	pip3 install pre-commit
	pre-commit install
	pre-commit install-hooks


precommit_run:
	pre-commit run --all-files

precommit_run_diff:
	pre-commit run --all-files --show-diff-on-save
