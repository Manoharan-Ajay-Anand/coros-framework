pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        sh '''git submodule update --init --recursive
mkdir build
cd build
cmake ..
./echo'''
      }
    }

  }
}