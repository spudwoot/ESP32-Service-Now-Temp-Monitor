const char *HTML_CONTENT_Connection = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>



<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<link rel="icon" href="data:,">
<title>Configuration Settings</title>


<h1>Rest Configuration Settings</h1>
<form action="/get">
<div><B>GET or GET/POST</b></div><br> <select id="get-post" name="get-post"><option value="getpost">Get & Post</option><option value="post">Post Only</option></select></div>
<br>
<br>
Note: If using Service Now, the fields for a GET request are coded into the API.  If your project does not do a GET, please select POST only
<br>
<br>
<b>Input the Path to your server</b>
<div><input type="text" name="serverD"></div>
<br>
<h3>Please select how many fields you want to Post to the server</h3> 
<b>Number of Fields</b> 
<input type="number" id="fieldC" name="fieldC" min="0" max="9" onchange="showField()">
<div class="field-names"> 
<div id="one" style="display :none;">
    <span>Field Name 1: <input type="text" name="field1"> </span><span>Type of Data <select id="field1V" name="field1V" onchange="showField()"><option value="" selected>Choose Value Type</option><option value="Temperature">Temperature</option><option value="Humidity">Humidity</option><option value="MAC_address">MAC address</option><option value="Water_alert">Water Alert (true/false)</option><option value="reboot_time">Time since last reboot</option><option value="static_entry">Static Entry</option></select></span> <span id="extra1" style="display :none;"> Add your Static Entry Here <input type="text" id="static1"  name="static1"></span>    
</div>
<div id="two" style="display :none;">
    <span>Field Name 2: <input type="text" name="field2"> </span><span>Type of Data <select id="field2V" name="field2V" onchange="showField()"><option value="" selected>Choose Value Type</option><option value="Temperature">Temperature</option><option value="Humidity">Humidity</option><option value="MAC_address">MAC address</option><option value="Water_alert">Water Alert (true/false)</option><option value="reboot_time">Time since last reboot</option><option value="static_entry">Static Entry</option></select></span> <span id="extra2" style="display :none;"> Add your Static Entry Here <input type="text" id="static2"  name="static2"></span> 
</div>
<div id="three" style="display :none;">
    <span>Field Name 3: <input type="text" name="field3"> </span><span>Type of Data <select id="field3V" name="field3V" onchange="showField()"><option value="" selected>Choose Value Type</option><option value="Temperature">Temperature</option><option value="Humidity">Humidity</option><option value="MAC_address">MAC address</option><option value="Water_alert">Water Alert (true/false)</option><option value="reboot_time">Time since last reboot</option><option value="static_entry">Static Entry</option></select></span> <span id="extra3" style="display :none;"> Add your Static Entry Here <input type="text" id="static3"  name="static3"></span>    
</div>
<div id="four" style="display :none;">
    <span>Field Name 4: <input type="text" name="field4"> </span><span>Type of Data <select id="field4V" name="field4V" onchange="showField()"><option value="" selected>Choose Value Type</option><option value="Temperature">Temperature</option><option value="Humidity">Humidity</option><option value="MAC_address">MAC address</option><option value="Water_alert">Water Alert (true/false)</option><option value="reboot_time">Time since last reboot</option><option value="static_entry">Static Entry</option></select></span> <span id="extra4" style="display :none;"> Add your Static Entry Here <input type="text" id="static4"  name="static4"></span> 
</div>
<div id="five" style="display :none;">
    <span>Field Name 5: <input type="text" name="field5"> </span><span>Type of Data <select id="field5V" name="field5V" onchange="showField()"><option value="" selected>Choose Value Type</option><option value="Temperature">Temperature</option><option value="Humidity">Humidity</option><option value="MAC_address">MAC address</option><option value="Water_alert">Water Alert (true/false)</option><option value="reboot_time">Time since last reboot</option><option value="static_entry">Static Entry</option></select></span> <span id="extra5" style="display :none;"> Add your Static Entry Here <input type="text" id="static5"  name="static5"></span>    
</div>
<div id="six" style="display :none;">
    <span>Field Name 6: <input type="text" name="field6"> </span><span>Type of Data <select id="field6V" name="field6V" onchange="showField()"><option value="" selected>Choose Value Type</option><option value="Temperature">Temperature</option><option value="Humidity">Humidity</option><option value="MAC_address">MAC address</option><option value="Water_alert">Water Alert (true/false)</option><option value="reboot_time">Time since last reboot</option><option value="static_entry">Static Entry</option></select></span> <span id="extra6" style="display :none;"> Add your Static Entry Here <input type="text" id="static6"  name="static6"></span> 
</div>
<div id="seven" style="display :none;">
    <span>Field Name 7: <input type="text" name="field7"> </span><span>Type of Data <select id="field7V" name="field7V" onchange="showField()"><option value="" selected>Choose Value Type</option><option value="Temperature">Temperature</option><option value="Humidity">Humidity</option><option value="MAC_address">MAC address</option><option value="Water_alert">Water Alert (true/false)</option><option value="reboot_time">Time since last reboot</option><option value="static_entry">Static Entry</option></select></span> <span id="extra7" style="display :none;"> Add your Static Entry Here <input type="text" id="static7"  name="static7"></span> 
</div>
<div id="eight" style="display :none;">
    <span>Field Name 8: <input type="text" name="field8"> </span><span>Type of Data <select id="field8V" name="field8V" onchange="showField()"><option value="" selected>Choose Value Type</option><option value="Temperature">Temperature</option><option value="Humidity">Humidity</option><option value="MAC_address">MAC address</option><option value="Water_alert">Water Alert (true/false)</option><option value="reboot_time">Time since last reboot</option><option value="static_entry">Static Entry</option></select></span> <span id="extra8" style="display :none;"> Add your Static Entry Here <input type="text" id="static8"  name="static8"></span>    
</div>
 <div id="nine" style="display :none;">
    <span>Field Name 9: <input type="text" name="field9"> </span><span>Type of Data <select id="field9V" name="field9V" onchange="showField()"><option value="" selected>Choose Value Type</option><option value="Temperature">Temperature</option><option value="Humidity">Humidity</option><option value="MAC_address">MAC address</option><option value="Water_alert">Water Alert (true/false)</option><option value="reboot_time">Time since last reboot</option><option value="static_entry">Static Entry</option></select></span> <span id="extra9" style="display :none;"> Add your Static Entry Here <input type="text" id="static9"  name="static9"></span> 
</div>
</div>
<br>

    
<h3>"Please input your username and password for both GET and POST"</h3> 
<b>Username:</b> <input type="text" name="susername">
<br>
<b>Password:</b> <input type="text" name="spassword">
<br>
<input type="submit" value="Submit">
</form><br>
</div>

<script>

function showField(){
var div = document.querySelectorAll('.field-names > div'); 
for(i=0;i<div.length; i++){
    e=div[i]
    if (i < fieldC.value){
        e.style.display = 'block'
    } else{
        e.style.display = 'none'
        //clear values
        var span2=e.getElementsByTagName("span"); 
        var d=span2[1].getElementsByTagName("select");
        d[0].value=""
        d=span2[0].getElementsByTagName("input")
        d[0].value=""
        d=span2[2].getElementsByTagName("input")
        d[0].value="" 
    }
    span2=e.getElementsByTagName("span");
    if (span2.length >=1){
        d=span2[1].getElementsByTagName("select");
        if(d.length = 1){
        if (d[0].value == "static_entry" ){
            span2[2].style.display = 'inline';
    }else{
        span2[2].style.display = 'none';
            }
        }
    }
}
}

</script>

</body>
</html>)rawliteral";
