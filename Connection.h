const char *HTML_CONTENT_Connection = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="icon" href="data:,">
    <title>Configuration Settings</title>
</head>
<body>
    <h2>Server Path</h2>
    <br>
    <h1>This is the path to your server and table.  Please use the REST API explorer to determine the exact path to the table<h2>
    <br>
    <h1>This program is set with static field names.  Those names are humidity, temperature, and mac_address.  Please make sure your table has those fields</h1>
    <br>
 
<form action="/get">
server: <input type="text" name="serverD">
<input type="submit" value="Submit">
</form><br>



</body>
</html>)rawliteral";