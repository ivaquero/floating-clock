#!/bin/bash

# GitHub Actions Local Testing Script
# This script helps test GitHub Actions workflows locally using act

echo "GitHub Actions Local Testing for Clouck"
echo "========================================"

# Check if act is installed
if ! command -v act &> /dev/null; then
    echo "❌ act is not installed. Installing..."
    echo "Please install act from: https://github.com/nektos/act"
    echo "On macOS: brew install act"
    echo "On Linux: curl https://raw.githubusercontent.com/nektos/act/master/install.sh | bash"
    exit 1
fi

# Display available workflows
echo "Available workflows:"
echo "1. CI Build (ci.yml) - Quick validation builds"
echo "2. Build Qt (build.yml) - Comprehensive builds"
echo "3. Release (release.yml) - Create releases"
echo "4. All workflows"
echo ""

# Function to run workflow
run_workflow() {
    local workflow=$1
    local event=$2

    echo "Running $workflow with event: $event"
    act -W .github/workflows/$workflow -e $event --dry-run
}

# Menu
read -p "Which workflow do you want to test? (1-4): " choice

case $choice in
    1)
        echo "Testing CI Build workflow..."
        run_workflow "ci.yml" "push"
        ;;
    2)
        echo "Testing Build Qt workflow..."
        run_workflow "build.yml" "push"
        ;;
    3)
        echo "Testing Release workflow..."
        # Create a mock release event
        cat > /tmp/release-event.json << EOF
        {
          "ref": "refs/tags/v1.0.0",
          "repository": {
            "name": "floating-clock",
            "owner": {
              "login": "ivaquero"
            }
          }
        }
        EOF
        run_workflow "release.yml" "/tmp/release-event.json"
        ;;
    4)
        echo "Testing all workflows..."
        act --dry-run
        ;;
    *)
        echo "Invalid choice. Exiting."
        exit 1
        ;;
esac

echo ""
echo "To run the workflows for real (not dry-run), remove the --dry-run flag"
echo "Example: act -W .github/workflows/ci.yml"
echo ""
echo "For local testing with Docker, you may need to use different images:"
echo "act -P ubuntu-latest=nektos/act-environments-ubuntu:18.04"
echo "act -P macos-latest=nektos/act-environments-macos:latest"
echo "act -P windows-latest=nektos/act-environments-windows:latest"
