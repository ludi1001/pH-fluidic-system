#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

String HOST = "10.190.209.142";
String PROTOCOL = "http://";
String PATH_PREFIX = "/system/";

// Listen on default port 5555, the webserver on the Yun
// will forward there all the HTTP requests for us.
YunServer server;

String formatResult(int,String="");

void setup() {
  Serial.begin(9600);

  // Bridge startup
  pinMode(13,OUTPUT);
  digitalWrite(13, HIGH);
  Bridge.begin();
  digitalWrite(13, LOW);
  
  Bridge.put("status", "idle");

  server.begin();
}

void loop() {
  // Get clients coming from server
  YunClient client = server.accept();
  
  // There is a new client?
  if (client) {
    process(client);
  }

  delay(50); // Poll every 50ms
}

void process(YunClient client) {
  // read the command
  String command = client.readStringUntil('/');
  command.trim();

  if(command == "ping") {
    client.print(formatResult(0, "\"ping\":\"yay\""));
    client.stop();
    
    //blink LED
    for(int i = 0; i < 3; ++i) {
        digitalWrite(13, HIGH);
        delay(300);
        digitalWrite(13, LOW);
        delay(300);
    }
  }
  else if(command == "measure") {
    client.print(F("{\"code\":0}"));
    client.stop();
    
    Bridge.put("status", "measure");
    
    ajax("status/measuring");
    //for now blink LED as well
    for(int i = 0; i < 5; ++i) {
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
    }
    String result = "result/";
    result += 6.2;
    ajax(result);
    ajax("status/idle");
    
    Bridge.put("status", "idle");
  }
  else if(command == "server") {
    //change the host
    String new_host = client.readStringUntil('/');
    new_host.trim();
    HOST = new_host;
    client.print(formatResult(0));
    client.stop();
  }
  else {
    String extra = "\"command\":\"";
    extra += command;
    extra += "\"";
    client.print(formatResult(1, extra));
    client.stop();
  }
}

void ajax(String url) {
  Process p;        // Create a process and call it "p"
  p.begin("curl");  // Process that launch the "curl" command
  p.addParameter(PROTOCOL + HOST + PATH_PREFIX + url); // Add the URL parameter to "curl"
  p.addParameter("--connect-timeout");
  p.addParameter("5"); //5 second timeout
  p.run();      // Run the process and wait for its termination
}

String formatResult(int exitCode, String extra) {
  String result = "{\"code\":";
  result += exitCode;
  result += ",\"host\":\"";
  result += HOST;
  result += "\"";
  if(extra != "") {
    result += ",";
    result += extra;
  }
  result += "}";
  return result;
}
