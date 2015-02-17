var express = require('express');
var io = require('../io');
var http = require('http');
var system = require('../fluidic-system');
var router = express.Router();

router.get('/', function(req, res, next) {
  res.send('{"code":0}');
});

router.get('/status/:status', function(req, res) {
    system.status = req.params.status;
    io.sockets.emit('status', system);
    res.json(system);
});

router.get('/result/:result', function(req, res) {
    var result = {
        'result': parseFloat(req.params.result)
    };
    io.sockets.emit('result', result);
    res.json(result);
});

io.on('connection', function (socket) {
    socket.emit('status', system);
  
    socket.on('measure', function (data) {
        console.log('measuring started');
        http.get('http://10.190.86.235/arduino/measure', function handle(res) {
            res.setEncoding('utf8');
            var total = 0;
            var data = [];
            res.on('data', function(chunk) {
                total += chunk.length;
                data.push(chunk);
            });
            res.on('end', function() {
                console.log(data.join());
            });
        });
    });
});

module.exports = router;
