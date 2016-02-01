import Foundation
import NedapIdReader


@objc(NedapReader) class NedapReader : CDVPlugin,
  IdHandConnectorObserver,
  InventorySessionDelegate,
  BarcodeSessionDelegate,
  ProgramSessionDelegate
  {
  
  //  var idHandConnector: IdHandConnector
  
  var idHandSettings:             IdHandSettings?
  var idHandConnector:            IdHandConnector?
  
  var inventorySession:           InventorySession?
  var barcodeSession:             BarcodeSession?
  var programmingSession:         ProgramSession?
  
  var callbackId:                 String!
  var inventorySessionCallbackId: String!
  var barcodeSessionCallbackId:   String!
  var programSessionCallbackId:   String!
  
  var connectedIdHand:            IdHand!
  var observationTimer:           NSTimer?
  
  var disableFeedback:            Bool!
  
  func configureSettings(object: AnyObject) -> Void {
    switch object["session"] as! String  {
      case "Session0":
        idHandSettings?.session = IdHandRFIDSessionType.Session0
      case "Session1":
        idHandSettings?.session = IdHandRFIDSessionType.Session1
      case "Session2":
        idHandSettings?.session = IdHandRFIDSessionType.Session2
      case "Session3":
        idHandSettings?.session = IdHandRFIDSessionType.Session3
      default:
        idHandSettings?.session = IdHandRFIDSessionType.Session1
    }
    self.disableFeedback = object["disableFeedback"] as! Bool
  }
  
  func connect(command: CDVInvokedUrlCommand) -> Void {
    self.callbackId = command.callbackId
    idHandSettings = IdHandSettings()
    configureSettings(command.arguments.first!)
    idHandConnector = IdHandConnector(idHandSettings: idHandSettings!)
    idHandConnector!.addObserver(self)
  }
  
  func disconnect(command: CDVInvokedUrlCommand) -> Void {
    if (self.inventorySession != nil) {
      self.inventorySession!.stop()
    }
    self.connectedIdHand.disconnect()
    let pluginResult = CDVPluginResult.init(status: CDVCommandStatus_OK, messageAsString: "Disconnected")
    self.commandDelegate?.sendPluginResult(pluginResult, callbackId: command.callbackId)
  }
  
  // MARK: RFID SESSION ********************
  
  func startObservingEpcs(command: CDVInvokedUrlCommand) -> Void {
    self.inventorySessionCallbackId = command.callbackId
    
    self.inventorySession = InventorySession(idHandConnector: self.idHandConnector!, idHandSettings : self.idHandSettings!, observationCounter: ObservationCounter())
    self.inventorySession?.delegate = self
    self.inventorySession?.start()
  }
  
  func stopObservingEpcs(command: CDVInvokedUrlCommand) -> Void {
    print("Shutting off the RFID Tag read session...")
    inventorySession!.stop()
    inventorySession!.cleanup()
    inventorySession!.delegate = nil
    
    let pluginResult = CDVPluginResult.init(status: CDVCommandStatus_OK, messageAsBool: true)
    self.commandDelegate?.sendPluginResult(pluginResult, callbackId: command.callbackId)
  }
  
  func currentObservations() -> Void {
    var epcObservationsArray = [AnyObject]()
    for epcObservation in inventorySession!.epcObservations() {
      epcObservationsArray.append([
        "hex": epcObservation.hex,
        "rssi": NSNumber.init(short: epcObservation.rssi/10) as Int,
        "times_observed": epcObservation.count
        ] as [String: AnyObject!])
    }
    let payload  = [
      "total_count":  inventorySession!.totalCount(),
      "unique_count": inventorySession!.uniqueCount(),
      "epcs":         epcObservationsArray
    ]
    let response = ["eventName": "onTagRead", "payload": payload]
    let pluginResult = CDVPluginResult.init(status: CDVCommandStatus_OK, messageAsDictionary: response as [NSObject : AnyObject] )
    pluginResult.setKeepCallbackAsBool(true)
    self.commandDelegate?.sendPluginResult(pluginResult, callbackId: self.inventorySessionCallbackId)
  }
  
//  deinit() {
//    self.inventorySession.stop()
//  }
  
  // MARK: IdHandConnectorObserver
  
  func idHandDidConnect(idHand: IdHand) {
    print("idHandDidConnect")
    self.connectedIdHand = idHand
    self.connectedIdHand.disableFeedback = disableFeedback
    
    let pluginResult = CDVPluginResult.init(status: CDVCommandStatus_OK, messageAsDictionary: connectedIdHand.toDict() as! [NSObject: AnyObject!])
    self.commandDelegate?.sendPluginResult(pluginResult, callbackId: self.callbackId)
  }
  
  func idHandDidDisconnect(idHand: IdHand) {
    print("idHandDidDisconnect")
  }
  
  func idHandIsSelected(idHand: IdHand) {
    print("idHandIsSelected")
  }
  
  func idHandIsDeselected() {
    print("idHandIsDeselected")
  }
  
  func idHandSettingsUpdated() {
    print("idHandSettingsUpdated")
  }
  
  func idHandBatteryLevelUpdate(idHand : IdHand, batteryPercentage : Int) {
    print("idHandBatteryLevelUpdate")
  }
  
  func idHandBatteryWarning(idHand : IdHand, batteryPercentage : Int) {
    print("idHandBatteryWarning")
  }
  
  // MARK: InventorySessionDelegate
  
  func inventoryIdHandIsSelected() {
    print("inventoryIdHandIsSelected")
  }
  
  /// Callback when !D Hand deselected
  func inventoryIdHandIsDeselected() {
    print("inventoryIdHandIsDeselected")
  }
  
  /// Callback when !D Hand started reading
  func inventoryIdHandDidStartReading() {
    print("inventoryIdHandDidStartReading")
    let response = ["eventName": "idHandDidStartReading", "payload": []]
    let pluginResult = CDVPluginResult.init(status: CDVCommandStatus_OK, messageAsDictionary: response)
    pluginResult.setKeepCallbackAsBool(true)
    self.commandDelegate?.sendPluginResult(pluginResult, callbackId: self.inventorySessionCallbackId)
    observationTimer = NSTimer.scheduledTimerWithTimeInterval(0.5, target: self, selector: "currentObservations", userInfo: nil, repeats: true)
  }
  
  /// Callback when !D Hand stopped reading
  func inventoryIdHandDidStopReading() {
    print("inventoryIdHandDidStopReading");
    observationTimer?.invalidate()
    let response = ["eventName": "idHandDidStopReading", "payload": []]
    let pluginResult = CDVPluginResult.init(status: CDVCommandStatus_OK, messageAsDictionary: response)
    pluginResult.setKeepCallbackAsBool(true)
    self.commandDelegate?.sendPluginResult(pluginResult, callbackId: self.inventorySessionCallbackId)
  }
  
  /// Called when the battery level of the selected !D Hand has changed
  func inventoryIdHandBatteryLevelUpdate(idHand : IdHand, batteryPercentage : Int) {
    print("inventoryIdHandBatteryLevelUpdate")
  }
  
  /// Callback when !D Hand did receive a battery warning
  func inventoryIdHandBatteryWarning(idHand : IdHand, batteryPercentage : Int) {
    print("inventoryIdHandBatteryWarning")
  }
  
  /// Callback when error was encountered
  func inventoryDidEncounterError(error : NSError) {
    print("inventoryDidEncounterError")
  }
  
  // MARK: BARCODE SESSION ********************
  
  func startObservingBarcodes(command: CDVInvokedUrlCommand) -> Void {
    barcodeSessionCallbackId = command.callbackId
    
    barcodeSession = BarcodeSession(idHandConnector: idHandConnector!)
    barcodeSession?.delegate = self
    barcodeSession?.start()
  }
  
  func stopObservingBarcodes(command: CDVInvokedUrlCommand) -> Void {
    barcodeSession?.stop()
    barcodeSession?.cleanup()
    barcodeSession?.delegate = nil
    
    let pluginResult = CDVPluginResult.init(status: CDVCommandStatus_OK, messageAsBool: true)
    commandDelegate?.sendPluginResult(pluginResult, callbackId: command.callbackId)
  }
  
  // MARK: BarcodeSessionDelegate
  
  func barcodeIdHandDidStartReading() {
    print("barcodeIdHandDidStartReading")
  }
  
  
  func barcodeIdHandDidStopReading() {
    print("barcodeIdHandDidStopReading")
  }
  
  
  func barcodeIdHandDidRead() {
    print("barcodeIdHandDidRead")
    let payload = [
      "barcodeType": (barcodeSession?.barcodeType())!,
      "barcodeValue": (barcodeSession?.barcode())!
    ] as [String: String]
    let response = [
      "eventName": "barcodeIdHandDidRead",
      "payload": payload
    ] as [String: AnyObject]
    let pluginResult = CDVPluginResult.init(status: CDVCommandStatus_OK, messageAsDictionary: response)
    pluginResult.setKeepCallbackAsBool(true)
    self.commandDelegate!.sendPluginResult(pluginResult, callbackId: self.barcodeSessionCallbackId)
  }
  
  
  func barcodeIdHandReadFailed(errorMessage: String) {
    print("barcodeIdHandReadFailed")
    let response = ["eventName": "barcodeIdHandReadFailed", "payload": false]
    let pluginResult = CDVPluginResult.init(status: CDVCommandStatus_OK, messageAsDictionary: response)
    pluginResult.setKeepCallbackAsBool(true)
    self.commandDelegate!.sendPluginResult(pluginResult, callbackId: self.barcodeSessionCallbackId)
  }
  
  
  func barcodeIdHandIsSelected() {
    print("barcodeIdHandIsSelected")
  }
  
  
  func barcodeIdHandIsDeselected() {
    print("barcodeIdHandIsDeselected")
  }
  
  
  func barcodeIdHandBatteryWarning(idHand: IdHand, batteryPercentage: Int) {
    print("barcodeIdHandBatteryWarning")
  }
  
  
  func barcodeDidEncounterError(error : NSError) {
    print("barcodeDidEncounterError")
  }
  
  
  // MARK: PROGRAM SESSION *****************
  
  func startProgrammingSession(command: CDVInvokedUrlCommand) -> Void {
    print("startProgrammingSession")
    programSessionCallbackId = command.callbackId
    programmingSession = ProgramSession(idHandConnector: idHandConnector!, idHandSettings: idHandSettings!)
    programmingSession?.delegate = self
    programmingSession?.start()
  }
  
  func stopProgrammingSession(command: CDVInvokedUrlCommand) -> Void {
    print("stopProgrammingSession")
    programmingSession?.delegate = nil
    programmingSession?.stop()
    programmingSession?.cleanup()
  }
  
  func writeToTag(command: CDVInvokedUrlCommand) -> Void {
    let hexValue = command.arguments.first as! String
    programmingSession?.programHex(hexValue)
    programSessionCallbackId = command.callbackId;
  }
  
  // MARK: ProgramSessionDelegate
  
  func programIdHandDidStartProgramming() {
    let response = ["eventName": "idHandDidStartProgramming", "payload": true]
    let pluginResult = CDVPluginResult.init(status: CDVCommandStatus_OK, messageAsDictionary: response)
    pluginResult.setKeepCallbackAsBool(true)
    commandDelegate?.sendPluginResult(pluginResult, callbackId: programSessionCallbackId)
  }
  
  
  func programIdHandDidStopProgramming() {
    let response = ["eventName": "idHandDidStopProgramming", "payload": true]
    let pluginResult = CDVPluginResult.init(status: CDVCommandStatus_OK, messageAsDictionary: response)
    pluginResult.setKeepCallbackAsBool(true)
    commandDelegate?.sendPluginResult(pluginResult, callbackId: programSessionCallbackId)
  }
  
  
  func programIdHandDidProgram() {
    let response = ["eventName": "idHandDidProgram", "payload": true]
    let pluginResult = CDVPluginResult.init(status: CDVCommandStatus_OK, messageAsDictionary: response)
    pluginResult.setKeepCallbackAsBool(true)
    commandDelegate?.sendPluginResult(pluginResult, callbackId: programSessionCallbackId)
  }
  
  
  func programIdHandDidNotProgram(errorMessage: String) {
    print("didNotProgram")
    print(errorMessage)
    let response = ["eventName": "idHandDidNotProgram", "payload": errorMessage]
    let pluginResult = CDVPluginResult.init(status: CDVCommandStatus_OK, messageAsDictionary: response)
    pluginResult.setKeepCallbackAsBool(true)
    commandDelegate?.sendPluginResult(pluginResult, callbackId: programSessionCallbackId)
  }
  
  
  func programIdHandIsSelected() {

  }
  
  
  func programIdHandIsDeselected() {

  }
  
  
  func programIdHandBatteryWarning(idHand : IdHand, batteryPercentage : Int) {

  }
  
  
  func programDidEncounterError(error : NSError) {
    print("didEncounterError")
  }


}