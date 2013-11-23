
export BOOST_ROOT=/home/yury/boost/boost_1_47_0
#export BOOSR_LIBRARYDIR=/usr/lib64
export SOLUTION_NAME=puzzle_4_week_solutions

export BUILD_TYPE=Debug
if [ "$1" == 'Release' ];
then
	export BUILD_TYPE=Release
fi

export BUILD_FOLDER=_build_"$BUILD_TYPE"_32

if [ ! -d $BUILD_FOLDER ];
then
	mkdir $BUILD_FOLDER
fi

cd $BUILD_FOLDER
cmake -DVERBOSE=ON -DSOLUTION_NAME=$SOLUTION_NAME -DCMAKE_BUILD_TYPE=$BUILD_TYPE -G "Unix Makefiles" ../ 
cd ../

