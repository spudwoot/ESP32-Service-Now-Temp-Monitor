const char *HTML_CONTENT_Connection2 = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="icon" href="data:,">
    <title>Configuration Settings</title>
</head>
<body>
    <h2>Username</h2>
    <br>
    <h1>Recomendation is to create a Web service account with write rights to your table as well as:</h1>
    <br>
    <h1>
     <ul>
  <li>snc_platform_rest_api_access</li>
  <li>cmdb_read</li>
  <li>web_service_admin</li>
  <li>rest_service</li>
  <li>rest_api_explorer</li>
</ul> 
</h1>
 


<form action="/get">
username: <input type="text" name="susername">
<input type="submit" value="Submit">
</form><br>



</body>
</html>)rawliteral";