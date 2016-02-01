class NedapReader {

  constructor(idHand) {
    this.manufacturer       = idHand.manufacturer
    this.serial             = idHand.serial
    this.name               = idHand.name
    this.observingTags      = false
    this.observingBarcodes  = false

    this.observedEpcs       = null
    this.observedBarcodes   = [] 

    this._handlers          = {
      'idHandDidStartReading':        [],
      'idHandDidStopReading':         [],
      'onTagRead':                    [],
      'barcodeIdHandDidStartReading': [],
      'barcodeIdHandDidStopReading':  [],
      'barcodeIdHandDidRead':         [],
      'barcodeIdHandReadFailed':      [],
      'onDisconnect':                 []
    }
  }

  on(eventName, callback) {
    if (this._handlers.hasOwnProperty(eventName)) {
      this._handlers[eventName].push(callback)
    }
  }

  emit() {
    var args = Array.prototype.slice.call(arguments)
    var eventName = args.shift();

    if (!this._handlers.hasOwnProperty(eventName)) {
      return false
    }

    if ((typeof this._handlers[eventName][0]) == 'function') {
      this._handlers[eventName].forEach((callback) => {
        callback.apply(undefined, args)
      })
    }

    return true
  }

  startObservingEpcs() {
    this.observingTags = true
    console.info("NedapReader: Ready to observe RFID tags. Press the button on the !D Hand to start.")
    return new Promise((resolve, reject) => {
      cordova.exec((success) => {
        this.emit(success.eventName, success.payload)
        resolve(success)
      }, (error) => {
        console.error("NedapReader: Unable to start the RFID observation session.")
        reject(error)
      }, "NedapReader", "startObservingEpcs", []) 
    })
  }

  stopObservingEpcs() {
    this.observingTags = false
    return new Promise((resolve, reject) => {
      cordova.exec((success) => {
        // this.emit(success.eventName, success.payload)
        console.info("NedapReader: RFID observation session closed.")
        resolve(success)
      }, (error) => {
        reject(error)
      }, "NedapReader", "stopObservingEpcs", []) 
    })
  }

  startObservingBarcodes() {
    this.observingBarcodes = true
    console.info("NedapReader: Ready to observe barcodes. Press the button on the !D Hand to start.")
    return new Promise((resolve, reject) => {
      cordova.exec((success) => {
        this.emit(success.eventName, success.payload)
        resolve(success)
      }, (error) => {
        console.error("NedapReader: Unable to start the barcode observation session.")
        reject(error)
      }, "NedapReader", "startObservingBarcodes", []) 
    })
  }

  stopObservingBarcodes() {
    this.observingBarcodes = false
    return new Promise((resolve, reject) => {
      cordova.exec((success) => {
        // this.emit(success.eventName, success.payload)
        console.info("NedapReader: Barcode observation session closed.")
        resolve(success)
      }, (error) => {
        reject(error)
      }, "NedapReader", "stopObservingBarcodes", []) 
    })
  }

  static connect() {
    console.info('NedapReader: Initiating connection with !D Hand')
    return new Promise((resolve, reject) => {
      cordova.exec((idHand) => { 
        console.info('NedapReader: Successfully connected !D Hand')
        var reader = new NedapReader(idHand)

        reader.on('onTagRead', (result) => {
          reader.observedEpcs = result
          console.info("NedapReader: ", result)
        })

        reader.on('idHandDidStartReading', () => {
          console.info("NedapReader: idHandDidStartReading")
        })

        reader.on('idHandDidStopReading', () => {
          console.info("NedapReader: idHandDidStopReading")
        })

        reader.on('barcodeIdHandDidStartReading', () => {
          console.info("NedapReader: barcodeIdHandDidStartReading")
        })

        reader.on('barcodeIdHandDidStopReading', () => {
          console.info("NedapReader: barcodeIdHandDidStopReading")
        })

        reader.on('barcodeIdHandDidRead', (result) => {
          reader.observedBarcodes.push(result)
          console.info("NedapReader: barcodeIdHandDidRead", result)
        })

        console.info('NedapReader: Initiating NedapReader object..')
        resolve(reader) 
      }, (error) => {
        reject(error)
      }, "NedapReader", "connect", []);
    })
  }

  disconnect() {
    return new Promise((resolve, reject) => {
      cordova.exec((success) => {
        console.info('NedapReader: Disconnected !D Hand')
        resolve(success)
      }, (error) => {
        console.error('NedapReader: Failed to disconnect from !D Hand')
        reject(error)
      }, "NedapReader", "disconnect", [])
    })
  }

}

module.exports = {
  connect:        NedapReader.connect,
}