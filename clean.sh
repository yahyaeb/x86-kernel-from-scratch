#!/bin/bash
set -e

docker ps -q | xargs -r docker stop

# Remove all containers
docker ps -aq | xargs -r docker rm -f

# Remove all images
docker images -q | xargs -r docker rmi -f
