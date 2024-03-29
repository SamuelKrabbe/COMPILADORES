# For Powershell
# To use type '.\Make.ps1' to use the defaultTarget function
# or '.\Make.ps1 <function>' to use a specific function

$PROG = "principal.cpp", "scanner.cpp", "parser.cpp"
$HEADERS = "scanner.h", "token.h", "parser.h"
$ORIGIN = "analisadorLexico.exe"
$INPUTFILE = "input.mj"

$CFLAGS = "-pedantic", "-Wall"

# Target: all
function all {
    compile
}

# Target: compile
function compile {
    Write-Host ""
    Write-Host "Compiling..."
    Write-Host ""
    & g++ $PROG $HEADERS -o $ORIGIN $CFLAGS
}

# Target: run
function run {
    Write-Host ""
    Write-Host "Running..."
    Write-Host ""
    & ./$ORIGIN $INPUTFILE
}

# Target: clean
function clean {
    Write-Host ""
    Write-Host "Cleaning..."
    Write-Host ""
    Remove-Item $ORIGIN
    Write-Host "Origin file removed"
    Write-Host ""
}

# Target: help
function help {
    Write-Host ""
    Write-Host "For more commands type: '.\Make.ps1 commands'"
    Write-Host ""
}

# Target: commands
function commands {
    Write-Host ""
    Write-Host "type: "
    Write-Host "    '.\Make.ps1 compile' to compile"
    Write-Host ""
    Write-Host "    '.\Make.ps1 run' to run the compiled file"
    Write-Host ""
    Write-Host "    '.\Make.ps1 clean' to remove the origin(.exe) file"
    Write-Host ""
}

# Target: default
function defaultTarget {
    Write-Host "----------------------------------------------"
    compile
    run
    help
}

# Parse arguments
if ($args.Count -eq 0) {
    defaultTarget
} else {
    foreach ($arg in $args) {
        Invoke-Expression $arg
    }
}
