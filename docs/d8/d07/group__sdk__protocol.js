var group__sdk__protocol =
[
    [ "TelemetryDatagram", "d8/d07/group__sdk__protocol.html#d7/df0/structQuasarSDK_1_1Datagrams_1_1TelemetryDatagram", [
      [ "marker", "d8/d07/group__sdk__protocol.html#a0ea604dd26c415c8f380323b91bdba56", null ],
      [ "version", "d8/d07/group__sdk__protocol.html#ab22abc2906422da61885ac6c8e6a1a59", null ],
      [ "latitude", "d8/d07/group__sdk__protocol.html#a76714bdbc5c536fa77dfb14533ff82a9", null ],
      [ "longitude", "d8/d07/group__sdk__protocol.html#ac155e35fdeebafc89723a51520fb9fe6", null ],
      [ "altitude", "d8/d07/group__sdk__protocol.html#a2b13d276aee0d9fd646c8fa3647e869b", null ],
      [ "velocity_course", "d8/d07/group__sdk__protocol.html#a1cc3289ef7b73c8e162d430e00c7f5ef", null ],
      [ "velocity_east", "d8/d07/group__sdk__protocol.html#a968a00cf20306de6c97d362b509abefe", null ],
      [ "velocity_north", "d8/d07/group__sdk__protocol.html#a5dfe7d6fa7d6ccc819aa45ee3ebfbb56", null ],
      [ "velocity_vertical", "d8/d07/group__sdk__protocol.html#aeb6f0994320a1acbcb6aaff582c8ee42", null ],
      [ "pitch", "d8/d07/group__sdk__protocol.html#a34c057a0378030db67bd6a129f37d938", null ],
      [ "roll", "d8/d07/group__sdk__protocol.html#a1d3228afa3a1d6773954f40c1e519eb9", null ],
      [ "yaw", "d8/d07/group__sdk__protocol.html#a21cd490f6191f66678f55b4c242a10cf", null ],
      [ "course", "d8/d07/group__sdk__protocol.html#acaa2fde7e3fad7df8f5755347603d17b", null ],
      [ "time", "d8/d07/group__sdk__protocol.html#a35486a245cee06695e814e1bcac83aac", null ],
      [ "satellites", "d8/d07/group__sdk__protocol.html#aa306fbda3e6f642c3668c299361d25d0", null ],
      [ "crc16", "d8/d07/group__sdk__protocol.html#a4438e0df9f58b1861feb3fc659f52534", null ]
    ] ],
    [ "TelemetryRequest", "d8/d07/group__sdk__protocol.html#d7/d26/structQuasarSDK_1_1Datagrams_1_1TelemetryRequest", [
      [ "marker", "d8/d07/group__sdk__protocol.html#a0ea604dd26c415c8f380323b91bdba56", null ],
      [ "init_flag", "d8/d07/group__sdk__protocol.html#a210e06aa846736988dbee1b9f1bb4464", null ],
      [ "port", "d8/d07/group__sdk__protocol.html#a8e0798404bf2cf5dabb84c5ba9a4f236", null ],
      [ "interval_ms", "d8/d07/group__sdk__protocol.html#a90ade0bc499be730c6d20696fffaf4f7", null ],
      [ "crc16", "d8/d07/group__sdk__protocol.html#a4438e0df9f58b1861feb3fc659f52534", null ]
    ] ],
    [ "PlannerAppendDatagram", "d8/d07/group__sdk__protocol.html#d4/d94/structQuasarSDK_1_1Datagrams_1_1PlannerAppendDatagram", [
      [ "marker", "d8/d07/group__sdk__protocol.html#a0ea604dd26c415c8f380323b91bdba56", null ],
      [ "id", "d8/d07/group__sdk__protocol.html#a4fc3a0c58dfbd1e68224521185cb9384", null ],
      [ "r", "d8/d07/group__sdk__protocol.html#acfb1795eb860b37ae4a0cf5007525b11", null ],
      [ "ip", "d8/d07/group__sdk__protocol.html#a69ddb9c845da426f636d9dd0dbed4e7e", null ],
      [ "port", "d8/d07/group__sdk__protocol.html#a8e0798404bf2cf5dabb84c5ba9a4f236", null ],
      [ "lat", "d8/d07/group__sdk__protocol.html#a7972334534f68166121a6e51b0aac2d6", null ],
      [ "lon", "d8/d07/group__sdk__protocol.html#aa96391e04b5977c50b96d77bea86a01d", null ],
      [ "cnt", "d8/d07/group__sdk__protocol.html#ae1d905c6ac1a0c9b96dca16153917334", null ],
      [ "len", "d8/d07/group__sdk__protocol.html#a8aed22e2c7b283705ec82e0120515618", null ],
      [ "command", "d8/d07/group__sdk__protocol.html#af161fc144504ebd2d6a3a287a47efcc0", null ]
    ] ],
    [ "PlannerRemoveDatagram", "d8/d07/group__sdk__protocol.html#d2/d1c/structQuasarSDK_1_1Datagrams_1_1PlannerRemoveDatagram", [
      [ "marker", "d8/d07/group__sdk__protocol.html#a0ea604dd26c415c8f380323b91bdba56", null ],
      [ "id", "d8/d07/group__sdk__protocol.html#a4fc3a0c58dfbd1e68224521185cb9384", null ],
      [ "r", "d8/d07/group__sdk__protocol.html#acfb1795eb860b37ae4a0cf5007525b11", null ],
      [ "lat", "d8/d07/group__sdk__protocol.html#a7972334534f68166121a6e51b0aac2d6", null ],
      [ "lon", "d8/d07/group__sdk__protocol.html#aa96391e04b5977c50b96d77bea86a01d", null ],
      [ "cnt", "d8/d07/group__sdk__protocol.html#ae1d905c6ac1a0c9b96dca16153917334", null ],
      [ "len", "d8/d07/group__sdk__protocol.html#a8aed22e2c7b283705ec82e0120515618", null ]
    ] ],
    [ "PlannerResponseDatagram", "d8/d07/group__sdk__protocol.html#df/d11/structQuasarSDK_1_1Datagrams_1_1PlannerResponseDatagram", [
      [ "marker", "d8/d07/group__sdk__protocol.html#a0ea604dd26c415c8f380323b91bdba56", null ],
      [ "id", "d8/d07/group__sdk__protocol.html#a4fc3a0c58dfbd1e68224521185cb9384", null ],
      [ "cnt", "d8/d07/group__sdk__protocol.html#ae1d905c6ac1a0c9b96dca16153917334", null ]
    ] ]
];