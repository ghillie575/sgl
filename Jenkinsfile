pipeline {
     agent {
        docker {
            image 'ubuntu:latest'
        }
    }
    stages {
        stage('Install Dependencies') {
            steps {
                script {
                    try {
                        // Install additional libraries (example for Ubuntu)
                        sh '''
                            apt-get update >> /dev/null
                            apt-get install -y zip g++ cmake curl git libglfw3 libglfw3-dev >> /dev/null
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
                    // Build the project
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
                            cp ./XandO ./out/XandO
                            cp -r ./include ./out/include
                            cp ./libsgl.so ./out/libsgl.so
                            cp -r ./engine ./out/engine
                            cp -r ./scenes ./out/scenes
                        '''
                        
                        // Create a timestamp for the zip file
                        def timestamp = new Date().format("yyyyMMdd-HHmm")
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

        stage('Release') {
            when {
                expression {
                    // Get the latest commit message
                    def commitMessage = sh(script: 'git log -1 --pretty=%B', returnStdout: true).trim()
                    // Check if the commit message contains 'release-'
                    return commitMessage.contains('release-')
                }
            }
            steps {
                script {
                    try {
                        // Get the latest commit message
                        def commitMessage = sh(script: 'git log -1 --pretty=%B', returnStdout: true).trim()
                        
                        // Use a regex to find 'release-' and capture the next 6 characters
                            
                            // Upload the zip file
                            sh "curl -X 'POST' \
  'http://git-release:8080/upload?token=%24jSOIMWvgfPO%24%26%23OPJPIRS&project=sgl&version=${commitMessage}' \
  -H 'accept: */*' \
  -H 'Content-Type: multipart/form-data' \
  -F 'file=@${env.ZIP_FILE_NAME}'"
                    } catch (Exception e) {
                        error "Failed to upload to GRU: ${e.message}"
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