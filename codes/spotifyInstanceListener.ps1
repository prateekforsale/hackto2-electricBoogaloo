# Powershell Code to open spotify with a SOCKS5 proxy Configuration
# get spotify process
$spotify = Get-Process spotify -ErrorAction SilentlyContinue
for (; ; ) {
    if ($spotify) {
        # try gracefully first
        echo "Spotify is running"
        break
    }
    if ((Get-WMIObject -Class Win32_Process -Filter "Name='PowerShell.EXE'" | Where { $_.CommandLine -Like "*spotify_Proxy*" } | Select Handle, CommandLine | FT -AutoSize) -and (-not($spotify))) {
        & spotify
        break
    }
    else {
        echo "nothing is running"
    }
}
Remove-Variable spotify
