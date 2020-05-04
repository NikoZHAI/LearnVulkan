SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
mkdir -p $SCRIPT_DIR/Tera/build && cd $SCRIPT_DIR/Tera/build && \
	cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$SCRIPT_DIR/shared/tera .. && make install &&\
mkdir -p $SCRIPT_DIR/SimViewer/build && cd $SCRIPT_DIR/SimViewer/build &&\
	cmake -DCMAKE_BUILD_TYPE=Debug -DTERA_HOME=$SCRIPT_DIR/shared/tera .. && make 
