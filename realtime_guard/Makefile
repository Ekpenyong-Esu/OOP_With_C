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

install_python_doc:
	pip install sphinx sphinx-rtd-theme autodoc

install_python_deps:
	pip install pydeps

install_python_deps_tools:
	pip install pydeps pipdeptree graphviz pylint sfood
	pip install git+https://github.com/thebjorn/pydeps.git

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

python_doc_init:
	mkdir -p docs/python
	cd docs/python && sphinx-quickstart

python_doc_generate:
	cd docs/python && make html

python_dependency_graph:
	pydeps path/to/your/python/code --max-bacon=10 --cluster --output-format png --output python_deps.png

python_deps_pipdeptree:
	pipdeptree --graph-output png > python_deps_tree.png

python_deps_pylint:
	pylint --import-graph=import_graph.dot path/to/your/package
	dot -Tpng import_graph.dot -o pylint_deps.png

python_deps_snakefood:
	sfood path/to/your/package > sf.pkgs
	sfood-graph sf.pkgs | dot -Tpng -o snakefood_deps.png

python_deps_modulegraph:
	python -m modulegraph path/to/your/main.py > module_graph.dot
	dot -Tpng module_graph.dot -o module_deps.png

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
