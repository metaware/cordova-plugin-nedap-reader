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

#### 5. `reader.startProgrammingSession()`

Start the tag writing/programming session.

---

#### 6. `reader.stopProgrammingSession()`

Closes the tag writing/programming session.

---

#### 7. `reader.writeToTag(value)`

Prepares the value that needs to be written to the Tag.

---

#### 8. `reader.disconnect()`

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


#### 7. `reader.observingEpcs` (Boolean)

Returns `true` if the RFID observation session is active and the !D Hand is observing RFID Tags, returns `false` otherwise.

---

#### 8. `reader.observingBarcodes` (Boolean)

Returns `true` if the Barcode observation session is active and the !D Hand is observing Barcodes, returns `false` otherwise.

---

#### 9. `reader.observedEpcs` (Object)

Object containing observed EPCs data, following properties are available:

```
{
  total_count: N,
  unique_count: N,
  epcs: [{
    hex: "hex value",
    rssi: -N,
    times_observed: N
  }]
}
```
---

#### 10. `reader.serial` (String)

Returns the serial number of the connected !D Hand.

---

#### 10. `reader.manufacturer` (String)

Returns the Manufacturer name of the connected !D Hand.

---

#### 11. `reader.name` (String)

Returns the Name of the connected !D Hand.

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

#### 5. `barcodeIdHandReadFailed`

Example: 

```
reader.on('barcodeIdHandReadFailed', function() {
  // do something interesting
})
```

#### 6. `idHandDidNotProgram`

Example:

```
reader.on('idHandDidNotProgram', function(reason) {
  // returns back with the reason why the idHand was unable to program an RFID Tag.
})
```

#### 7. `idHandDidProgram`

Example: 

```
reader.on('idHandDidProgram', function() {
  // called when ID Hand is able to successfully write data to the tag
})
```

#### 8. `idHandDidStartProgramming`

Example: 

```
reader.on('idHandDidStartProgramming', function() {
  // called when ID hand begins tag writing.
})
```

#### 9. `idHandDidStopProgramming`

Example: 

```
reader.on('idHandDidStartProgramming', function() {
  // called when ID hand finishes tag writing
})
```