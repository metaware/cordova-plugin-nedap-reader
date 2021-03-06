class NedapReader {

  constructor(idHand) {
    this.manufacturer       = idHand.manufacturer
    this.serial             = idHand.serial
    this.name               = idHand.name
    this.outputPower        = null
    this.session            = null

    this.observingTags      = false
    this.observingBarcodes  = false
    this.programmingSessionActive = false

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
      'onDisconnect':                 [],
      'idHandDidNotProgram':          [],
      'idHandDidProgram':             [],
      'idHandDidStartProgramming':    [],
      'idHandDidStopProgramming':     [],
      'idHandBatteryLevelUpdate':     []
    }
  }
  
  set outputPower(newOutputPower) {
    if (newOutputPower) {
      cordova.exec((success) => {
        console.info('NedapReader: Updated output power to', newOutputPower)
      }, (error) => {
        console.info('NedapReader: Failed to update output power')
      }, "NedapReader", "setOutputPower", [newOutputPower])
    }
  }
  
  set session(newSession) {
    // possible values include: "Session0", "Session1", "Session2", "Session3"
    var validValues = ["Session0", "Session1", "Session2", "Session3"]
    if (validValues.indexOf(newSession) == -1) {
      console.error('Invalid value for session. Valid values are: "Session0", "Session1", "Session2", "Session3"')
      return
    }
    if (newSession) {
      cordova.exec((success) => {
        console.info('NedapReader: Updated session to', newSession)
      }, (error) => {
        console.info('NedapReader: Failed to update session')
      }, "NedapReader", "setSession", [newSession])
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
    this.observedEpcs = null
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
    this.observedBarcodes  = []
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

  startProgrammingSession() {
    console.info("NedapReader: Tag Programming session opened. Make sure you call `reader.writeToTag(value)` and then press the button on the !D Hand.")
    this.programmingSessionActive = true
    cordova.exec((success) => {
      this.emit(success.eventName, success.payload)
    }, () => {
      //
    }, "NedapReader", "startProgrammingSession", [])
  }

  stopProgrammingSession() {
    console.info("NedapReader: Tag programming session closed.")
    this.programmingSessionActive = false
    cordova.exec(() => {

    }, () => {
      //
    }, "NedapReader", "stopProgrammingSession", [])
  }

  writeToTag(value) {
    console.info("Writetotag called")
    cordova.exec((success) => {
      this.emit(success.eventName, success.payload)
    }, (error) => {
      //
    }, "NedapReader", "writeToTag", [value]) 
  }

  static connect(settings) {
    console.info('NedapReader: Initiating connection with !D Hand')
    return new Promise((resolve, reject) => {
      cordova.exec((idHand) => { 
        console.info('NedapReader: Successfully connected !D Hand')
        var reader = new NedapReader(idHand)

        reader.on('onTagRead', (result) => {
          reader.observedEpcs = result
          console.info("NedapReader: ", result)
          console.groupCollapsed("Observed EPC's (table format)")
          console.table(result.epcs)
          console.groupEnd()
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

        reader.on('barcodeIdHandReadFailed', () => {
          console.error("NedapReader: barcodeIdHandReadFailed")
        })

        reader.on('idHandDidNotProgram', (reason) => {
          console.error("NedapReader: idHandDidNotProgram", reason)
        })

        reader.on('idHandDidStartProgramming', () => {
          console.info("NedapReader: idHandDidStartProgramming")
        })

        reader.on('idHandDidStopProgramming', () => {
          console.info("NedapReader: idHandDidStopProgramming")
        })

        reader.on('idHandDidProgram', () => {
          console.info("NedapReader: idHandDidProgram")
        })

        reader.on('idHandBatteryLevelUpdate', (percentage) => {
          console.info("NedapReader: idHandBatteryLevelUpdate", percentage)
        })

        console.info('NedapReader: Initiating NedapReader object..')
        resolve(reader) 
      }, (error) => {
        reject(error)
      }, "NedapReader", "connect", [settings]);
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