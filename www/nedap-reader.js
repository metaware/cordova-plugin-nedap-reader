'use strict';

var _createClass = (function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ('value' in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; })();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError('Cannot call a class as a function'); } }

var NedapReader = (function () {
  function NedapReader(idHand) {
    _classCallCheck(this, NedapReader);

    this.manufacturer = idHand.manufacturer;
    this.serial = idHand.serial;
    this.name = idHand.name;
    this.observingTags = false;
    this.observingBarcodes = false;

    this.observedEpcs = null;
    this.observedBarcodes = [];

    this._handlers = {
      'idHandDidStartReading': [],
      'idHandDidStopReading': [],
      'onTagRead': [],
      'barcodeIdHandDidStartReading': [],
      'barcodeIdHandDidStopReading': [],
      'barcodeIdHandDidRead': [],
      'barcodeIdHandReadFailed': [],
      'onDisconnect': []
    };
  }

  _createClass(NedapReader, [{
    key: 'on',
    value: function on(eventName, callback) {
      if (this._handlers.hasOwnProperty(eventName)) {
        this._handlers[eventName].push(callback);
      }
    }
  }, {
    key: 'emit',
    value: function emit() {
      var args = Array.prototype.slice.call(arguments);
      var eventName = args.shift();

      if (!this._handlers.hasOwnProperty(eventName)) {
        return false;
      }

      if (typeof this._handlers[eventName][0] == 'function') {
        this._handlers[eventName].forEach(function (callback) {
          callback.apply(undefined, args);
        });
      }

      return true;
    }
  }, {
    key: 'startObservingEpcs',
    value: function startObservingEpcs() {
      var _this = this;

      this.observingTags = true;
      console.info('NedapReader: Ready to observe RFID tags. Press the button on the !D Hand to start.');
      return new Promise(function (resolve, reject) {
        cordova.exec(function (success) {
          _this.emit(success.eventName, success.payload);
          resolve(success);
        }, function (error) {
          console.error('NedapReader: Unable to start the RFID observation session.');
          reject(error);
        }, 'NedapReader', 'startObservingEpcs', []);
      });
    }
  }, {
    key: 'stopObservingEpcs',
    value: function stopObservingEpcs() {
      this.observingTags = false;
      return new Promise(function (resolve, reject) {
        cordova.exec(function (success) {
          // this.emit(success.eventName, success.payload)
          console.info('NedapReader: RFID observation session closed.');
          resolve(success);
        }, function (error) {
          reject(error);
        }, 'NedapReader', 'stopObservingEpcs', []);
      });
    }
  }, {
    key: 'startObservingBarcodes',
    value: function startObservingBarcodes() {
      var _this2 = this;

      this.observingBarcodes = true;
      console.info('NedapReader: Ready to observe barcodes. Press the button on the !D Hand to start.');
      return new Promise(function (resolve, reject) {
        cordova.exec(function (success) {
          _this2.emit(success.eventName, success.payload);
          resolve(success);
        }, function (error) {
          console.error('NedapReader: Unable to start the barcode observation session.');
          reject(error);
        }, 'NedapReader', 'startObservingBarcodes', []);
      });
    }
  }, {
    key: 'stopObservingBarcodes',
    value: function stopObservingBarcodes() {
      this.observingBarcodes = false;
      return new Promise(function (resolve, reject) {
        cordova.exec(function (success) {
          // this.emit(success.eventName, success.payload)
          console.info('NedapReader: Barcode observation session closed.');
          resolve(success);
        }, function (error) {
          reject(error);
        }, 'NedapReader', 'stopObservingBarcodes', []);
      });
    }
  }, {
    key: 'disconnect',
    value: function disconnect() {
      return new Promise(function (resolve, reject) {
        cordova.exec(function (success) {
          console.info('NedapReader: Disconnected !D Hand');
          resolve(success);
        }, function (error) {
          console.error('NedapReader: Failed to disconnect from !D Hand');
          reject(error);
        }, 'NedapReader', 'disconnect', []);
      });
    }
  }], [{
    key: 'connect',
    value: function connect() {
      console.info('NedapReader: Initiating connection with !D Hand');
      return new Promise(function (resolve, reject) {
        cordova.exec(function (idHand) {
          console.info('NedapReader: Successfully connected !D Hand');
          var reader = new NedapReader(idHand);

          reader.on('onTagRead', function (result) {
            reader.observedEpcs = result;
            console.info('NedapReader: ', result);
          });

          reader.on('idHandDidStartReading', function () {
            console.info('NedapReader: idHandDidStartReading');
          });

          reader.on('idHandDidStopReading', function () {
            console.info('NedapReader: idHandDidStopReading');
          });

          reader.on('barcodeIdHandDidStartReading', function () {
            console.info('NedapReader: barcodeIdHandDidStartReading');
          });

          reader.on('barcodeIdHandDidStopReading', function () {
            console.info('NedapReader: barcodeIdHandDidStopReading');
          });

          reader.on('barcodeIdHandDidRead', function (result) {
            reader.observedBarcodes.push(result);
            console.info('NedapReader: barcodeIdHandDidRead', result);
          });

          console.info('NedapReader: Initiating NedapReader object..');
          resolve(reader);
        }, function (error) {
          reject(error);
        }, 'NedapReader', 'connect', []);
      });
    }
  }]);

  return NedapReader;
})();

module.exports = {
  connect: NedapReader.connect
};