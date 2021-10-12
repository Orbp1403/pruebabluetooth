
const btSerial = new (require('bluetooth-serial-port')).BluetoothSerialPort();

//Generic Error Handler for the BT Serial Port library as requires error functions
const errFunction = (err) =>{
    if(err){
        console.log('Error', err);
    }else{
      console.log("Entro a error")
    }
 };
 
 // Connecting to BT device can take a few seconds so a little console.log to keep you entertained.
 console.log("Starting Server");
 btSerial.on('found', function(address, name) {
     if(name.toLowerCase().includes('grupo')){
 
       btSerial.findSerialPortChannel(address, function(channel) {
         btSerial.connect(address, channel, function() {
           btSerial.on('data', function(bufferData) {
             console.log(Buffer.from(bufferData).toString());
             btSerial.write(Buffer.from('From Node With Love\n'), errFunction);
           });
         }, ()=>{
           console.log("error al conectar")
         });
       },(err)=>{
        console.log('Error en encontrar el canal')
       });
     }else{
       console.log('Not connecting to: ', name);
     }
 });
 
 // Starts looking for Bluetooth devices and calls the function btSerial.on('found'
 btSerial.inquire();