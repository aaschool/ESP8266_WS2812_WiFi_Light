void handleRoot() {
    digitalWrite ( signal_led, HIGH );
    String out = "<html><head><title>ESP8266 WS2812 WiFi Lighting</title></head>";
    out += "<body style='background-color:gray'><center>";
    out += "<span style='display:block; width:100%; font-size:2em; font-family:Verdana; text-align:center'>ESP8266 WS2812 WiFi Lighting</span><br/>";

    out += "<a href='off'><span style='display:block; background-color:black; width:100%; height:3em;'>Off</span></a><br/>";
    
    out += "<a href='brighten'><span style='display:block; background-color:white; width:100%; height:3em;'>Brighter</span></a><br/>";
    out += "<a href='dim'><span style='display:block; background-color:black; foreground-color:white; width:100%; height:3em;'>Dimmer</span></a><br/>";

    out += "<a href='faster'><span style='display:block; background-color:light-grey; width:100%; height:3em;'>Faster</span></a><br/>";
    out += "<a href='slower'><span style='display:block; background-color:dark-grey; foreground-color:white; width:100%; height:3em;'>Slower</span></a><br/>";

    out += "<a href='white'><span style='display:block; background-color:white; width:100%; height:3em;'></span></a><br/>";
    out += "<a href='green'><span style='display:block; background-color:green; width:100%; height:3em;'></span></a><br/>";
    out += "<a href='yellow'><span style='display:block; background-color:yellow; width:100%; height:3em;'></span></a><br/>";
    out += "<a href='orange'><span style='display:block; background-color:orange; width:100%; height:3em;'></span></a><br/>";
    out += "<a href='red'><span style='display:block; background-color:red; width:100%; height:3em;'></span></a><br/>";
    out += "<a href='pink'><span style='display:block; background-color:pink; width:100%; height:3em;'></span></a><br/>";
    out += "<a href='blue'><span style='display:block; background-color:blue; width:100%; height:3em;'></span></a><br/>";
    out += "<a href='black'><span style='display:block; background-color:black; width:100%; height:3em;'></span></a><br/>";
    out += "<a href='sinelon'><span style='display:block; background-color:white; width:100%; height:3em;'>Transition: sinelon</span></a><br/>";
    out += "<a href='bpm'><span style='display:block; background-color:white; width:100%; height:3em;'>Transition: bpm</span></a><br/>";
    out += "<a href='random'><span style='display:block; background-color:white; width:100%; height:3em;'>Transition: random</span></a><br/>";
    out += "<a href='gradient'><span style='display:block; background-color:white; width:100%; height:3em;'>Transition: gradient</span></a><br/>";
    out += "<a href='constant'><span style='display:block; background-color:white; width:100%; height:3em;'>Transition: constant</span></a><br/>";
    out += "</center></body>";
    out += "</html>";
    server.send ( 200, "text/html", out );
    digitalWrite ( signal_led, LOW );
}

void handleNotFound() {
    digitalWrite ( signal_led, HIGH );
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for ( uint8_t i = 0; i < server.args(); i++ ) {
        message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
    }
    server.send ( 404, "text/plain", message );
    digitalWrite ( signal_led, LOW );
}