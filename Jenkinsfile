pipeline {
    agent any

    stages {
        stage('Install Dependencies') {
            steps {
                script {
                    try {
                        // Install additional libraries (example for Ubuntu)
                        sh '''
                            apt-get update
                            apt-get install -y zip g++ cmake git libglfw3 libglfw3-dev
                        '''
                    } catch (Exception e) {
                        error "Failed to install dependencies: ${e.message}"
                    }
                }
            }
        }

        stage('Build') {
            steps {
                script {
                    try {
                        // Configure and build the project
                        sh 'cmake .'
                        sh 'cmake --build . --config Release'
                    } catch (Exception e) {
                        error "Build failed: ${e.message}"
                    }
                }
            }
        }

        stage('Package') {
            steps {
                script {
                    try {
                        // Ensure the out directory exists
                        sh 'mkdir -p out'
                        
                        // Copy necessary files to the out directory
                        sh '''
                            cp ./XandO out/XandO
                            cp -r ./engine out/engine
                            cp -r ./scenes out/scenes
                        '''
                        
                        // Create a timestamp for the zip file
                        def timestamp = new Date().format("yyyyMMdd-HHmmss")
                        env.ZIP_FILE_NAME = "build-sgl-${timestamp}.zip"
                        
                        // Create the zip file with the timestamp
                        sh '''
                            cd out
                            zip -r "${ZIP_FILE_NAME}" *
                            mv "${ZIP_FILE_NAME}" ../
                            cd ..
                        '''
                    } catch (Exception e) {
                        error "Packaging failed: ${e.message}"
                    }
                }
            }
        }

        stage('Collect Artifacts') {
            steps {
                script {
                    try {
                        // Archive the build zip file as an artifact
                        archiveArtifacts artifacts: "${env.ZIP_FILE_NAME}", fingerprint: true
                        
                        // Upload the zip file
                        sh "curl -X 'POST' \
  'http://git-release:8080/upload?token=%24jSOIMWvgfPO%24%26%23OPJPIRS&project=sgl&version=${timestamp}' \
  -H 'accept: */*' \
  -H 'Content-Type: multipart/form-data' \
  -F 'file=@${env.ZIP_FILE_NAME}'"
                    } catch (Exception e) {
                        error "Failed to collect artifacts or upload: ${e.message}"
                    }
                }
            }
        }

        stage('Cleanup') {
            steps {
                script {
                    try {
                        // Remove all build resources
                        sh '''
                            echo 'Cleaning up...'
                            rm -rf build
                            rm -rf out
                            rm -f "${ZIP_FILE_NAME}"
                        '''
                    } catch (Exception e) {
                        error "Cleanup failed: ${e.message}"
                    }
                }
            }
        }
    }
}
