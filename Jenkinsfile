pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        sh 'git submodule update --init --recursive'
        sh 'mkdir build'
        sh 'cd build'
        sh 'cmake ..'
        sh 'make echo'
      }
    }
  }
}