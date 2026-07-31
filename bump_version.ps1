param(
    [Parameter(Mandatory=$true)]
    [string]$NewVersion   # e.g. "v1.4.0" (with the "v" prefix, matching your git tags)
)

Write-Host "Bumping all component references to version: $NewVersion" -ForegroundColor Cyan

# 1. Update the root idf_component.yml (strip leading "v" for the internal metadata field)
$rootYml = "idf_component.yml"
$versionNoV = $NewVersion -replace '^v', ''

if (Test-Path $rootYml) {
    (Get-Content $rootYml) -replace '^version:\s*".*"', "version: `"$versionNoV`"" | Set-Content $rootYml
    Write-Host "Updated $rootYml -> version: $versionNoV"
} else {
    Write-Host "WARNING: $rootYml not found at BSP root" -ForegroundColor Yellow
}

# 2. Find every examples/*/main/idf_component.yml and bump its pinned dependency version
$exampleYmls = Get-ChildItem -Path "examples" -Recurse -Filter "idf_component.yml" -File

if ($exampleYmls.Count -eq 0) {
    Write-Host "No example idf_component.yml files found under examples/" -ForegroundColor Yellow
} else {
    foreach ($file in $exampleYmls) {
        $content = Get-Content $file.FullName
        $updated = $content -replace '^\s*version:\s*".*"', "    version: `"$NewVersion`""
        Set-Content -Path $file.FullName -Value $updated
        Write-Host "Updated $($file.FullName) -> version: $NewVersion"
    }
}

Write-Host "`nDone. Review the diffs with 'git diff' before committing." -ForegroundColor Green