/*global cordova, data*/

var data = {
    surveys:[]
};

var app = {
    isScanning: false,
    
    initialize: function() {
        document.addEventListener('deviceready', this.onDeviceReady.bind(this), false);
        
    },

    onDeviceReady: function() {
        var id;
        var scanButton = document.getElementById("Scan");
        var stopButton = document.getElementById("Stop");
        scanButton.addEventListener("click",function(){
             app.isScanning = true;
             document.getElementById("data").innerHTML = "";
             app.scanning();
        });
        stopButton.addEventListener("click",function(){
            app.isScanning = false;
        });
        
    },
    
    scanning: function(){
        var id = setInterval(request, 1000);
        function request(){
            if(app.isScanning){
                var xhr = new XMLHttpRequest;
                var parentDisplay = document.getElementById("data");
                xhr.open("GET","http://192.168.4.1", true);
                xhr.send();
                xhr.onreadystatechange = processRequest;
                function processRequest(e){
                    if(xhr.readyState === 4 && xhr.status === 200){
                        var deviceData = JSON.parse(xhr.responseText);
                        data.surveys.push(deviceData);
                        var childDisplay = document.createElement("li");
                        childDisplay.innerHTML = xhr.responseText;
                        parentDisplay.appendChild(childDisplay);
                    }
                }
            } else if(!app.isScanning){
                clearInterval(id);
                app.storeData();
            }
        }
    },
    
    
    storeData: function(){
        var storedData = JSON.stringify(data, null, '\t');
        data.surveys = [];
        var fileName = app.getCurrentTime() + ".json";
        window.resolveLocalFileSystemURL(cordova.file.externalApplicationStorageDirectory,function(fileSystem){
           fileSystem.getDirectory("OpenTopo",{create: true},function(dir){
              dir.getFile(fileName,{create: true, exclusive: true},function(fileEntry){
                  fileEntry.createWriter(function(fileWriter){
                     var blob = new Blob([storedData], {type: 'text/plain'});
                     fileWriter.write(blob);
                  });
              });
           }); 
        });
        
        
        
    },
    
    getCurrentTime: function(){
        var date = new Date();
        var dd = date.getDate();
        var mm = date.getMonth()+1;//January is 0, so always add + 1
        var yyyy = date.getFullYear();
        if(dd<10){dd='0'+dd;}
        if(mm<10){mm='0'+mm;}
        var hours = date.getHours();
        var minutes = "0" + date.getMinutes();
        var seconds = "0" + date.getSeconds();
        var formattedTime = hours + '_' + minutes.substr(-2) + '_' + seconds.substr(-2);
        var now = dd + '_' + mm + '_' + yyyy + '_' + formattedTime;
        return now;
    }
    
        
};

app.initialize();