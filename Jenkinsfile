pipeline {
    agent any

    stages {
        stage('Install Dependencies') {
            steps {
                script {
                    // Install additional libraries (example for Ubuntu)
                    sh '''
                     apt-get update
                     apt-get install -y zip g++ cmake git libglfw3 libglfw3-dev
                    '''
                }
            }
        }

        stage('Build') {
            steps {
                script {
                    // Configure and build the project
                    sh 'cmake .'
                    sh 'cmake --build . --config Release'
                }
            }
        }

        stage('Package') {
            steps {
                script {
                    // Ensure the out directory exists
                    sh 'mkdir -p out'
                    
                    // Copy necessary files to the out directory
                    sh 'cp ./XandO out/XandO'
                    sh 'cp -r ./engine out/engine'
                    sh 'cp -r ./scenes out/scenes'
                    
                    // Create a timestamp for the zip file
                    def timestamp = new Date().format("yyyyMMdd-HHmmss")
                    def zipFileName = "build-sgl-${timestamp}.zip"
                    
                    // Create the zip file with the timestamp
                    sh "cd out && zip -r ${zipFileName} * && mv ${zipFileName} ../ && cd .."
                    
                    // Store the zip file name in an environment variable for later use
                    env.ZIP_FILE_NAME = zipFileName
                }
            }
        }

        stage('Collect Artifacts') {
            steps {
                // Archive the build zip file as an artifact
                archiveArtifacts artifacts: "${env.ZIP_FILE_NAME}", fingerprint: true
            }
        }

        stage('Cleanup') {
            steps {
                script {
                    // Remove all build resources
                    sh '''
                        echo 'Cleaning up...'
                        rm -rf build
                        rm -rf out
                        rm -f ${ZIP_FILE_NAME}
                    '''
                }
            }
        }
    }
}