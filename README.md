# cordova-plugin-nedap-reader

> Cordova Plugin to be used with Nedap's !D Hand 2.

# API

- Instantiate a `NedapReader` instance

```
NedapReader.connect()
  .then(function(reader) {
    // returns an instance of NedapReader
  })
  .catch(function(error) {
    // capture the error here..
  })
```


#### 1. `reader.startObservingEpcs()`

Initiates an RFID observation session.

---


#### 2. `reader.stopObservingEpcs()`

Closes RFID observation session.

---

#### 3. `reader.startObservingBarcodes()`

Initiates a Barcode observation session.

---

#### 4. `reader.stopObservingBarcodes()`

Closes barcode observation session.

---

#### 5. `reader.disconnect()`

Disconnects the reader. 

```
reader.disconnect()
  .then(function() {
    // successfully disconnected the reader.
  })
```

---

#### 6. `reader.on(eventName, callback)`

Add callbacks on interesting events. Check the supported events section for name and type of events that can be listened to.

---

### Supported Events:

#### 1. `idHandDidStartReading`

Example:

```
reader.on('idHandDidStartReading', function() {
  // do something interesting
})
```


#### 2. `idHandDidStopReading`

Example: 

```
reader.on('idHandDidStopReading', function() {
  // do something interesting
})
```

#### 3. `onTagRead`

`onTagRead` initiates a stream of events, and the callback is continuously called untill `reader.stopObservingEpcs()` is called.


Example: 

```
reader.on('onTagRead', function(result) {
  // result is an object with the following structure:
  // {
  //  "unique_count": N,
  //  "total_count": N,
  //  "epcs": [{ hex: "hexvalue", rssi: -N, times_observed: N }]
  // }
})
```

#### 4. `barcodeIdHandDidRead`

Example: 

```
reader.on('barcodeIdHandDidRead', function(result) {
  // result is an object with the following structure:
  // {
  //   "barcodeValue": "value"
  //   "barcodeType":  "barcodetype"
  // }
})
```