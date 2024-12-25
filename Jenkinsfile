pipeline {
    agent any

    stages {
        stage('Install Dependencies') {
            steps {
                script {
                    // Install additional libraries (example for Ubuntu)
                    // You can modify this command based on your OS and required libraries
                    sh '''
                     apt-get update
                     apt-get install -y libglfw3 libglfw3-dev
                    '''
                }
            }
        }

        stage('Build') {
            steps {
                script {
                        sh 'cmake .'
                        sh 'cmake --build . --config Release'
                }
            }
        }

        stage('Package') {
            steps {
                script {
                    // Create a release package (e.g., a zip file)
                    sh 'cd build && cp ./XandO ../out/XandO && cp -r ./engine ../out/engine && cp ./scenes ../out/scenes && cd ../'
                    sh 'cd out && zip -r build.zip * && mv build.zip ../ && cd ../ && rm -r out'
                }
            }
        }

        stage('Collect Artifacts') {
            steps {
                archiveArtifacts artifacts: 'build.zip', fingerprint: true
            }
        }
    }
}