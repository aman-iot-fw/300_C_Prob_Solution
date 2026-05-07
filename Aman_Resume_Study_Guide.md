# Aman Yadav — Complete Resume Interview Study Guide
### 10+ Hours of Deep Technical Content | Every Keyword Explained

---

> **How to use this guide:** Each section is structured as: Concept → Deep Explanation → Code Example → Data Linkage → Interview Q&A. Study 2–3 sections per day. Every answer is written so you can speak it directly to an interviewer.

---

# PART 1: BLE PROTOCOL STACK

## 1.1 BLE 5.x Architecture

### What it is
BLE (Bluetooth Low Energy) 5.x is a layered protocol stack. Think of it like the OSI model but specific to BLE. The layers from bottom to top are:

```
Application Layer
    ↓
GATT (Generic Attribute Profile)
    ↓
ATT (Attribute Protocol)
    ↓
SMP (Security Manager Protocol) ← runs in parallel
    ↓
L2CAP (Logical Link Control and Adaptation Protocol)
    ↓
HCI (Host Controller Interface)   ← split between Host and Controller
    ↓
Link Layer
    ↓
Physical Layer (PHY)
```

The **Host** runs on your application MCU (your firmware). The **Controller** runs on the BLE radio chip. In an integrated SoC like CC2340R5, both are on the same chip.

### BLE 5.x vs BLE 4.x — Key Differences

| Feature | BLE 4.2 | BLE 5.0+ |
|---|---|---|
| Max PHY speed | 1 Mbps | 2 Mbps (LE 2M PHY) |
| Long range | No | Yes (LE Coded PHY, 125kbps) |
| Advertising data | 31 bytes | 255 bytes (Extended Advertising) |
| Advertising channels | 3 | Up to 37 (Extended) |
| Advertising sets | 1 | Multiple simultaneous |
| Periodic Advertising | No | Yes |
| Channel Selection | CSA #1 | CSA #2 (better hopping) |

### How to explain this in interview
*"BLE 5.x brought four major improvements: 2M PHY for speed, Coded PHY for range, Extended Advertising for larger payloads, and improved channel selection algorithm CSA#2. In my smart meter project, I used BLE 5.3 and leveraged the 2M PHY for faster data transfer and 1M PHY as fallback for reliability."*

---

## 1.2 GAP State Machine

### What it is
GAP (Generic Access Profile) defines how BLE devices **discover** each other and **connect**. It defines device roles and states.

### GAP Roles
- **Advertiser** — broadcasts packets (typically peripheral/sensor)
- **Scanner** — listens for advertisers (typically central/phone/gateway)
- **Peripheral** — slave in a connection
- **Central** — master in a connection

### GAP State Machine (Peripheral Side)

```
STANDBY
   |
   ↓ Start advertising
ADVERTISING ──────────────────────────────┐
   |                                      |
   | (Connection Request from Central)    | (Scan Request → Scan Response)
   ↓                                      ↓
CONNECTION ESTABLISHMENT           SCANNING RESPONSE SENT
   |                                      |
   ↓                                      ↓
CONNECTED (Peripheral Role)        Back to ADVERTISING
   |
   | (Timeout / Disconnect)
   ↓
STANDBY
```

### Code Example — Starting BLE Advertisement on CC2340R5 (SimpleLink SDK)

```c
/* GAP Advertisement parameters */
static uint8_t advertData[] = {
    0x02,  // Length
    GAP_ADTYPE_FLAGS,
    GAP_ADTYPE_FLAGS_GENERAL | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,
    0x05,  // Length
    GAP_ADTYPE_LOCAL_NAME_SHORT,
    'M', 'e', 't', 'r'
};

/* Set advertisement data */
GapAdv_setParam(advHandle, GAP_ADV_PARAM_PRIMARY_PHY, &primaryPhy);
GapAdv_setParam(advHandle, GAP_ADV_PARAM_SECONDARY_PHY, &secondaryPhy);
GapAdv_loadByHandle(advHandle, GAP_ADV_DATA_TYPE_ADV,
                    sizeof(advertData), advertData);

/* Enable advertising */
GapAdv_enable(advHandle, GAP_ADV_ENABLE_OPTIONS_USE_MAX, 0);
```

### Data Linkage to Your Resume
In your smart meter project (OES8800-211), you managed the **GAP peripheral/central dual role**. This means your device advertised as a peripheral to smartphones, AND simultaneously scanned as a central to discover other meters. This is called **multi-role operation**.

### Interview Q&A

**Q: What happens when two BLE devices try to advertise on the same channel at the same time?**
A: "This is called an advertising collision. BLE uses three dedicated advertising channels (37, 38, 39) which are spread across the 2.4GHz band to avoid Wi-Fi overlap. Each advertiser introduces a random backoff delay (advDelay, 0–10ms) before each advertising event to reduce collision probability. In practice, the scanner will catch the advertisement on the next interval."

**Q: What is the difference between directed and undirected advertising?**
A: "Undirected advertising (ADV_IND) is broadcast to any scanner. Directed advertising (ADV_DIRECT_IND) contains the target device's address and only that specific device can respond with a connection request. It's used for fast reconnection — for example, when a smart meter needs to reconnect quickly to a known gateway after a BLE reset."

---

## 1.3 GATT Server/Client

### What it is
GATT (Generic Attribute Profile) is the layer that defines **how data is organized and exchanged** after a connection is established. It uses a client-server model.

- **GATT Server** = holds the data (your embedded device, smart meter, sensor)
- **GATT Client** = reads/writes the data (smartphone app, gateway)

### GATT Hierarchy

```
GATT Server
└── Service (e.g., Energy Metering Service — UUID: 0x181D)
    ├── Characteristic (e.g., Active Power — UUID: 0x2A70)
    │   ├── Value (e.g., 2300 Watts)
    │   ├── CCCD (Client Characteristic Configuration Descriptor)
    │   │   └── Enables Notify/Indicate from client
    │   └── User Description Descriptor
    └── Characteristic (e.g., Cumulative Energy — UUID: 0x2A74)
        └── Value (e.g., 1250 kWh)
```

### GATT Operations

| Operation | Direction | Requires ACK? | Use Case |
|---|---|---|---|
| Read | Client → Server (request), Server → Client (response) | Yes | Read sensor value on demand |
| Write with Response | Client → Server | Yes | Send command, confirm received |
| Write without Response | Client → Server | No | Fast streaming, audio |
| Notify | Server → Client | No | Streaming sensor data |
| Indicate | Server → Client | Yes | Critical alerts |

### Code Example — Custom GATT Service Definition (CC2340R5)

```c
/* Energy Metering Profile - Custom Service UUID */
#define ENERGY_SERVICE_UUID    0x1234
#define POWER_CHAR_UUID        0x1235
#define ENERGY_CHAR_UUID       0x1236

/* GATT Attribute Table */
static gattAttribute_t energyAttrTbl[] = {
    /* Service Declaration */
    {
        { ATT_BT_UUID_SIZE, primaryServiceUUID },
        GATT_PERMIT_READ,
        0,
        (uint8_t *)&energyServiceUUID
    },

    /* Active Power Characteristic Declaration */
    {
        { ATT_BT_UUID_SIZE, characterUUID },
        GATT_PERMIT_READ,
        0,
        &powerProps  // GATT_PROP_READ | GATT_PROP_NOTIFY
    },

    /* Active Power Characteristic Value */
    {
        { ATT_UUID_SIZE, powerCharUUID },
        GATT_PERMIT_READ,
        0,
        powerValue  // uint32_t, in Watts
    },

    /* Active Power CCCD */
    {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8_t *)powerCCCDTable  // Client writes 0x0001 to enable notify
    },
};

/* Send notification when power changes */
void Energy_notifyPower(uint16_t connHandle, uint32_t powerWatts) {
    attHandleValueNoti_t noti;
    noti.handle = powerValueHandle;
    noti.len = sizeof(powerWatts);
    memcpy(noti.value, &powerWatts, sizeof(powerWatts));
    GATT_Notification(connHandle, &noti, FALSE);
}
```

### Data Linkage to Your Resume
You built a **DLMS/COSEM gateway over BLE GATT** — this means you mapped DLMS meter data objects (OBIS codes) to custom GATT characteristics. The DLMS protocol is the IEC standard for smart meter communication. You essentially built a protocol bridge: DLMS ↔ GATT ↔ BLE.

### Interview Q&A

**Q: What is MTU negotiation in BLE and why did you use 247 bytes?**
A: "MTU (Maximum Transmission Unit) is the maximum number of bytes that can be transferred in a single ATT packet. The default is 23 bytes (20 bytes payload + 3 bytes ATT header). In BLE 4.2+, we can negotiate this up via ATT_EXCHANGE_MTU_REQ. I negotiated 247 bytes because DLMS meter frames can be up to 248 bytes, so fitting an entire DLMS PDU in one ATT packet eliminates fragmentation overhead and maximizes throughput. The theoretical max with LE Data Length Extension is 251 bytes payload."

**Q: What is the difference between Notify and Indicate?**
A: "Both push data from server to client without a client request. The key difference is acknowledgment: Notify is fire-and-forget — no ATT acknowledgment from client, so data could be lost. Indicate requires the client to send an ATT_HANDLE_VALUE_CONFIRMATION, guaranteeing delivery. For energy metering, I used Notify for real-time power readings (high-rate, loss-tolerant) and Indicate for billing data and alarms (must be delivered)."

---

## 1.4 L2CAP Channels

### What it is
L2CAP (Logical Link Control and Adaptation Protocol) provides **multiplexing, fragmentation, and reassembly** over the BLE link. It sits between ATT/SMP and the Link Layer.

### Key Concepts

**CID (Channel Identifier)** — Each logical channel has a CID:
- CID 0x0004 — ATT channel (GATT data)
- CID 0x0005 — Signaling channel (connection parameter updates)
- CID 0x0006 — SMP channel (security/pairing)
- CID 0x0040–0x007F — LE Credit-Based CoC (Connection-Oriented Channels)

**L2CAP CoC (Credit-Based Connection-Oriented Channels)** — BLE 4.1+ feature. Allows direct L2CAP channels without going through ATT/GATT. Much faster for bulk data transfer (file transfer, firmware OTA).

### Fragmentation/Reassembly

```
Application: 500 bytes to send
    ↓ L2CAP fragments into
Packet 1: [PB=10b, L2CAP header, first 27 bytes]  ← First fragment
Packet 2: [PB=01b, continuation, next 27 bytes]    ← Continuation
...
Packet N: [PB=01b, last bytes]                     ← Last fragment

PB = Packet Boundary flag in HCI header
```

### Data Linkage
In your resume, you mention "L2CAP channels" in the context of managing the full BLE stack. In the DLMS gateway, L2CAP fragmentation handled DLMS frames > MTU size. With MTU negotiated at 247 bytes, frames up to that size went unfragmented, improving throughput.

### Interview Q&A

**Q: When would you use L2CAP CoC instead of GATT for data transfer?**
A: "GATT has overhead per packet — ATT headers, handle lookups, CCCD checks. For bulk data like OTA firmware images, L2CAP CoC is better because it's a raw channel with credit-based flow control. You get higher throughput and lower CPU overhead. For example, if I needed to transfer a 256KB firmware image over BLE, I'd prefer L2CAP CoC over GATT Write-Without-Response streaming."

---

## 1.5 SMP — Security Manager Protocol

### What it is
SMP handles **pairing and key exchange** in BLE. It runs on its own L2CAP channel (CID 0x0006) and is responsible for establishing encrypted connections.

### Pairing Methods (BLE 4.x — Legacy Pairing)

| Method | Peripheral Capability | Central Capability | MITM Protection |
|---|---|---|---|
| Just Works | No I/O | No I/O | No |
| Passkey Entry | Display | Keyboard (or vice versa) | Yes |
| OOB (Out-of-Band) | OOB data | OOB data | Depends |

### LE Secure Connections (BLE 4.2+) — What You Used

LE Secure Connections (LESC) replaces legacy pairing with **ECDH (Elliptic Curve Diffie-Hellman)** key exchange. Even if you sniff the air interface, you cannot derive the keys (perfect forward secrecy).

```
LESC Pairing Flow:

Device A (Peripheral)          Device B (Central)
        |                              |
        |←—— Pairing Request ————————|
        |                              |
        |—— Pairing Response ————————→|
        |                              |
        | (Both generate ECDH key pairs: private key + public key)
        |                              |
        |←—— Public Key Exchange ————→|
        |                              |
        | (Both compute DHKey = ECDH(own_private, peer_public))
        |                              |
        | (Numeric Comparison: both display 6-digit code)
        | User confirms both match → authentication confirmed
        |                              |
        |←—— DHKey Check ————————————→|
        |                              |
        | Keys derived: LTK, IRK, CSRK |
        |                              |
        |←—— Encryption Start ————————|
        | AES-CCM encrypted link       |
```

### Code Example — LESC Pairing Configuration (CC2340R5)

```c
/* Configure GAP Bond Manager for LESC */
uint8_t  pairMode    = GAPBOND_PAIRING_MODE_INITIATE;
uint8_t  mitm        = TRUE;           // Man-in-the-middle protection
uint8_t  ioCap       = GAPBOND_IO_CAP_DISPLAY_YES_NO;  // Show 6-digit + Yes/No buttons
uint8_t  bonding     = TRUE;           // Store keys after pairing
uint8_t  lesc        = TRUE;           // Force LE Secure Connections
uint8_t  keyDist     = GAPBOND_KEYDIST_SENCKEY | GAPBOND_KEYDIST_MIDKEY;

GAPBondMgr_SetParameter(GAPBOND_PAIRING_MODE, sizeof(uint8_t), &pairMode);
GAPBondMgr_SetParameter(GAPBOND_MITM_PROTECTION, sizeof(uint8_t), &mitm);
GAPBondMgr_SetParameter(GAPBOND_IO_CAPABILITIES, sizeof(uint8_t), &ioCap);
GAPBondMgr_SetParameter(GAPBOND_BONDING_ENABLED, sizeof(uint8_t), &bonding);
GAPBondMgr_SetParameter(GAPBOND_LESC_SUPPORT, sizeof(uint8_t), &lesc);

/* Handle numeric comparison event */
void SMP_numericComparisonCallback(uint16_t connHandle, uint32_t numericCode) {
    /* Display numericCode on LCD */
    Display_printf(dispHandle, 3, 0, "Confirm: %06d", numericCode);
    /* Wait for user button press to confirm/deny */
}
```

### AES-CCM Encryption

After pairing, all data is encrypted using **AES-128 in CCM mode** (Counter with CBC-MAC):
- **Counter mode** provides encryption (confidentiality)
- **CBC-MAC** provides authentication (integrity)
- **128-bit LTK** (Long Term Key) is the encryption key

### Data Linkage
In your Araciv job: "LESC pairing with numeric comparison and passkey methods, managing secure key storage with wear leveling and implementing security mode 1 level 4 with AES-CCM encryption."

Security Mode 1 Level 4 = Authenticated LE Secure Connections pairing with encryption. This is the highest BLE security level.

### Interview Q&A

**Q: What is the difference between LTK, IRK, and CSRK?**
A: "LTK (Long Term Key) is used to re-encrypt a connection after the first pairing, avoiding a full re-pair on reconnection. IRK (Identity Resolving Key) is used to resolve a device's random resolvable private address (RPA) — BLE devices change their MAC address periodically for privacy; IRK lets a bonded device recognize the same peer even with a changed address. CSRK (Connection Signature Resolving Key) is used for signed writes — authenticating write operations without encryption."

**Q: What is wear leveling in the context of BLE key storage?**
A: "When storing bond keys to flash (LTK, IRK, CSRK), you're writing to NVM. Flash cells have a limited write cycle (~10,000–100,000 writes). If you always write to the same address, that cell wears out. Wear leveling distributes writes across a pool of flash pages. In practice on CC2340R5, I used the SNV (Simple Non-Volatile Storage) system which handles this internally. I exposed a clean API around SNV with a bond record structure so that on each re-pair, the new keys would be written to a different flash slot."

---

## 1.6 Attribute Database Design

### What it is
The attribute database is the structured data store inside the GATT server. Every GATT service, characteristic, and descriptor is an **attribute** — an addressable record with a handle, UUID, permissions, and value.

### Attribute Structure

```c
typedef struct {
    const gattAttrType_t  type;      // UUID (2-byte or 16-byte)
    uint8_t               permissions; // Read/Write/Auth permissions
    uint16_t              handle;    // Unique address (auto-assigned, starts at 0x0001)
    uint8_t               *pValue;   // Pointer to value
} gattAttribute_t;
```

### Design Principles

1. **Group related characteristics in a single service** — reduces discovery time
2. **Use 128-bit UUIDs for custom characteristics** — avoids Bluetooth SIG UUID conflicts
3. **Minimize characteristic value sizes** — ATT has overhead; pack data efficiently
4. **CCCD per notifiable characteristic** — each notification-capable char needs its own CCCD

### Data Packing Example (Smart Meter)

```c
/* Bad design — 4 separate characteristics, 4x overhead */
uint32_t activePower;     // Char 1
uint32_t reactivePower;   // Char 2
uint32_t voltage;         // Char 3
uint32_t current;         // Char 4

/* Better design — one packed characteristic for real-time data */
typedef struct __attribute__((packed)) {
    uint32_t activePower_W;     // 4 bytes
    uint32_t reactivePower_VAR; // 4 bytes
    uint16_t voltage_V_x10;     // 2 bytes (e.g., 2300 = 230.0V)
    uint16_t current_mA;        // 2 bytes (e.g., 10000 = 10.000A)
    uint8_t  powerFactor_x100;  // 1 byte  (e.g., 95 = 0.95)
    uint8_t  flags;             // 1 byte  (tamper, overload bits)
} __attribute__((packed)) MeterRealtimeData_t; // 14 bytes total
// Fits in 20 bytes default MTU, or send as single notify at 247-byte MTU
```

---

## 1.7 Connection Parameter Negotiation

### What it is
After establishing a BLE connection, both devices agree on timing parameters that control how often they exchange data.

### Parameters

| Parameter | Typical Range | Your Smart Meter Used | Effect |
|---|---|---|---|
| **Connection Interval** | 7.5ms – 4s | 7.5ms – 1s | How often devices exchange packets |
| **Slave Latency** | 0 – 499 events | Varies | Peripheral can skip N intervals to save power |
| **Supervision Timeout** | 100ms – 32s | Tuned per use-case | Link considered lost if no packet in this time |

### Negotiation Flow

```
Central (Phone/Gateway)          Peripheral (Smart Meter)
        |                                |
        |—— Connection REQ ——————————→  |
        |   (interval: 100ms, latency:0) |
        |                                |
        |←—— LL_CONNECTION_UPDATE_IND ——| (Peripheral requests new params)
        |   (interval: 20ms, latency:2)  |
        |                                |
        | (Central approves or denies)   |
        |—— LL_CONNECTION_UPDATE_IND ——→|
        | (New params take effect at     |
        |  a specific connection event)  |
```

### Power vs Throughput Trade-off

```
Short interval (7.5ms):
  - High throughput (good for DLMS data transfer)
  - High power (bad for battery)
  - 133 connection events per second

Long interval (1s) + slave latency 9:
  - Low throughput (fine for idle/polling)
  - Low power (peripheral wakes every 10s effectively)
  - Power saving = ~99% vs 7.5ms continuous
```

### Code Example

```c
/* Request connection parameter update from peripheral */
hciStatus_t status = HCI_LE_ConnectionUpdateCmd(
    connHandle,
    6,     // connIntervalMin = 6 * 1.25ms = 7.5ms
    800,   // connIntervalMax = 800 * 1.25ms = 1000ms
    9,     // slaveLatency = 9 events
    500    // supervisionTimeout = 500 * 10ms = 5000ms
);

/* Check that supervisionTimeout > (1 + slaveLatency) * connIntervalMax * 2
   500 * 10ms = 5000ms > (1+9) * 1000ms * 2 = 20000ms? NO! Fix:
   supervisionTimeout must be > 20s for latency=9, interval=1s
   Use: supervisionTimeout = 4000 (40 seconds) */
```

### Interview Q&A

**Q: How did you achieve <50µA sleep current in the smart meter project?**
A: "This was a multi-layered optimization. First, I used a long connection interval (1 second) with slave latency of 9, meaning the device only wakes every 10 connection events = once every 10 seconds when idle. Second, I put the CC2340R5 into its lowest power mode (Standby) between connection events using the RTC as the wakeup source — the RTC runs off a 32kHz crystal at ~0.5µA. Third, I optimized the application task to complete processing quickly and return to idle. Fourth, I retained only the minimum flash pages in retention during sleep. The combination of radio duty cycling and MCU standby mode gave us <50µA average current, enabling a 225mAh CR2032 to last 6+ months."

---

# PART 2: LINK LAYER & PHY

## 2.1 Link Layer State Machine

### What it is
The Link Layer (LL) is the lowest software layer of the BLE host controller, sitting just above the physical radio. It manages the actual radio operations.

### States

```
        ┌─────────────────────────────────────────────┐
        │           LINK LAYER STATE MACHINE           │
        │                                              │
        │   STANDBY ←─────────────────────────────┐   │
        │      │                                   │   │
        │      ├──→ ADVERTISING ──────────────────→┤   │
        │      │         │ (CONNECT_IND received)  │   │
        │      ├──→ SCANNING ────────────────────→ │   │
        │      │         │ (send CONNECT_IND)      │   │
        │      │         ↓                         │   │
        │      └──→ INITIATING ──────────────────→ │   │
        │                │ (connection created)    │   │
        │                ↓                         │   │
        │          CONNECTION ────────────────────→┘   │
        │         (MASTER or SLAVE role)               │
        └─────────────────────────────────────────────┘
```

### Connection Events

In connection state, the Link Layer schedules **connection events** at fixed intervals (the connection interval). During each event:

1. Master sends a packet (even empty)
2. Slave responds with a packet
3. They alternate until the event ends
4. Both go to sleep until the next event

```
Time →
|←— 7.5ms —→|←— 7.5ms —→|←— 7.5ms —→|

Event 1      Event 2      Event 3
[M→S][S→M]  [M→S][S→M]  [M→S][S→M]
            sleeping     sleeping
```

### Packet Structure

```
BLE Packet:
┌─────────┬──────────┬──────────┬──────────────────────┬─────────┐
│ Preamble│ Access   │ PDU      │ Payload               │  CRC    │
│ 1 byte  │ Address  │ Header   │ (0-255 bytes w/ DLE)  │ 3 bytes │
│         │ 4 bytes  │ 2 bytes  │                       │         │
└─────────┴──────────┴──────────┴──────────────────────┴─────────┘

Access Address: Unique per connection (randomly generated at setup)
                Advertising uses fixed: 0x8E89BED6
CRC: 24-bit CRC with polynomial x^24 + x^10 + x^9 + x^6 + x^4 + x^3 + x + 1
```

## 2.2 AFH — Adaptive Frequency Hopping

### What it is
BLE uses **frequency hopping** across 37 data channels (0-36) to avoid interference. AFH (Adaptive Frequency Hopping) allows the controller to **blacklist channels** that are noisy (Wi-Fi, microwave ovens, etc.).

### How it works

```
2.4GHz band: 2400MHz – 2483.5MHz
BLE Channels: Channel n = 2402 + 2n MHz (channel 0 = 2402MHz)

Wi-Fi overlaps:
- Wi-Fi Channel 1:  2412MHz ← overlaps BLE channels ~5–10
- Wi-Fi Channel 6:  2437MHz ← overlaps BLE channels ~13–19
- Wi-Fi Channel 11: 2462MHz ← overlaps BLE channels ~25–30

AFH Channel Map: 37-bit bitmap
0xFFFFFFFFFF = all channels enabled
0xFFFF8001FF = Wi-Fi Ch1 and Ch11 blocked (example)
```

### Channel Selection Algorithm (CSA #2 — BLE 5.x)

```c
/* CSA #2 — Channel Selection Algorithm 2 */
/* Used in BLE 5.0+ connections */
/* More uniform channel distribution vs CSA #1 */

uint8_t select_channel(uint16_t counter, uint8_t *channelMap, uint8_t numUsedChannels) {
    uint16_t prn_e = permutation(counter); // PRNG based on counter
    uint8_t  index = prn_e % numUsedChannels;
    return remapping_table[channelMap][index];
}
/* Result: better coexistence with other devices using CSA #1 */
```

### Data Linkage
In your resume: "link layer optimization with AFH, channel map updates" — this is exactly the above. You configured the channel map on CC2340R5 to avoid interference from Wi-Fi in smart meter installation environments (industrial/residential buildings with heavy Wi-Fi).

## 2.3 LE Coded PHY / 2M PHY Switching

### What it is
BLE 5.0 introduced three PHY options:

| PHY | Speed | Range | Power | Use Case |
|---|---|---|---|---|
| **LE 1M PHY** | 1 Mbps | ~30m | Medium | Default, universal |
| **LE 2M PHY** | 2 Mbps | ~20m | Lower | Speed-critical, short range |
| **LE Coded PHY (S=2)** | 500 kbps | ~60m | Higher | Moderate range |
| **LE Coded PHY (S=8)** | 125 kbps | ~200m | Highest | Maximum range |

### How Coded PHY achieves longer range
Coded PHY uses **FEC (Forward Error Correction)** — it transmits redundant data so the receiver can reconstruct corrupted bits. The trade-off: lower data rate.

```
1M PHY:     1 bit per symbol,  no redundancy
2M PHY:     2 bits per symbol, no redundancy (faster)
Coded S=2:  1 bit per 2 symbols (50% redundant)
Coded S=8:  1 bit per 8 symbols (87.5% redundant) → maximum range
```

### PHY Switching Based on RSSI (What You Did)

```c
/* Automatic PHY switching based on signal strength */
#define RSSI_2M_THRESHOLD    -65  /* dBm: switch to 2M if signal is strong */
#define RSSI_1M_THRESHOLD    -80  /* dBm: switch to 1M in middle range */
#define RSSI_CODED_THRESHOLD -90  /* dBm: switch to Coded PHY if weak */

void updatePHYBasedOnRSSI(uint16_t connHandle, int8_t rssi) {
    uint8_t newTxPhy, newRxPhy;

    if (rssi >= RSSI_2M_THRESHOLD) {
        newTxPhy = HCI_PHY_2_MBPS;
        newRxPhy = HCI_PHY_2_MBPS;
    } else if (rssi >= RSSI_1M_THRESHOLD) {
        newTxPhy = HCI_PHY_1_MBPS;
        newRxPhy = HCI_PHY_1_MBPS;
    } else {
        newTxPhy = HCI_PHY_CODED;
        newRxPhy = HCI_PHY_CODED;
    }

    /* Send LL_PHY_REQ to change PHY */
    HCI_LE_SetPhyCmd(connHandle,
                     0,           // all PHYs preference
                     newTxPhy,
                     newRxPhy,
                     HCI_PHY_OPT_S8);  // Use S=8 for coded
}

/* Register for RSSI read complete callback */
void BLE_processRSSIEvt(uint16_t connHandle, int8_t rssi) {
    static int8_t rssiHistory[4] = {0};
    static uint8_t idx = 0;

    // Rolling average to avoid flapping
    rssiHistory[idx++ % 4] = rssi;
    int16_t avg = 0;
    for (int i = 0; i < 4; i++) avg += rssiHistory[i];
    avg /= 4;

    updatePHYBasedOnRSSI(connHandle, (int8_t)avg);
}
```

### Data Linkage
You achieved 200m range in the mesh topology using Coded PHY. Standard BLE at 1M PHY gives ~30m. Coded PHY S=8 extends this to 200m+ in open environments.

### Interview Q&A

**Q: How does switching from 1M to 2M PHY reduce power consumption?**
A: "At 2M PHY, data is transmitted twice as fast. This means the radio is active for half the time per packet. Since the radio is the biggest power consumer in a BLE device, shorter radio-on time = less average power. The trade-off is slightly higher RF noise immunity requirement — you need a better RSSI to use 2M PHY reliably. That's why I implemented RSSI-based switching — above -65 dBm, 2M PHY is reliable and saves power; below -80 dBm, I fall back to 1M for reliability."

---

## 2.4 Packet CRC and Whitening

### CRC (Cyclic Redundancy Check)
BLE uses a **24-bit CRC** to detect bit errors in received packets. The CRC polynomial is applied to the PDU header and payload. If CRC fails, the packet is dropped and the controller requests retransmission (in connected mode).

```c
/* CRC verification happens in hardware on CC2340R5 */
/* If CRC fails, hardware signals error to Link Layer */
/* Link Layer increments error counter, schedules retransmission */

/* Soft CRC check example (for debugging/simulation): */
uint32_t ble_crc24(uint8_t *data, uint16_t len, uint32_t init) {
    uint32_t crc = init;
    for (uint16_t i = 0; i < len; i++) {
        for (uint8_t bit = 0; bit < 8; bit++) {
            uint8_t b = (data[i] >> bit) & 1;
            uint8_t feedback = (crc & 1) ^ b;
            crc >>= 1;
            if (feedback) crc ^= 0x00065B; // CRC-24 polynomial
        }
    }
    return crc;
}
```

### Whitening (Data Scrambling)
BLE applies a **data whitening** algorithm using a 7-bit LFSR to scramble PDU bits before transmission. This prevents long runs of 0s or 1s in the bit stream (which would cause DC offset issues in the radio).

```
Whitening sequence is initialized with the channel index.
Same sequence applied at transmitter (XOR) and receiver (XOR again = original data).
This is NOT encryption — it's just scrambling for radio signal quality.
```

---

# PART 3: BLE OPTIMIZATION

## 3.1 Connection Interval Tuning (7.5ms–4s)

### The Math Behind It

```
Connection Interval = N × 1.25ms  (N = 6 to 3200)

Minimum: 6 × 1.25 = 7.5ms  → 133 events/second, max throughput
Maximum: 3200 × 1.25 = 4s  → 0.25 events/second, minimum power
```

### Power Calculation Example

```
Assumptions:
- CC2340R5 Tx current: 4.6mA
- CC2340R5 Rx current: 5.9mA
- CC2340R5 Standby current: 0.7µA
- Connection event duration: ~500µs (1 packet each direction)

At 7.5ms interval (no slave latency):
  Active time: 500µs / 7500µs = 6.67%
  Average I = (0.0667 × 5.25mA) + (0.9333 × 0.7µA)
            ≈ 350µA + 0.65µA ≈ 350µA

At 1s interval, slave latency = 9:
  Device wakes every 10s (skips 9 events)
  Active time: 500µs / 10,000,000µs = 0.005%
  Average I = (0.00005 × 5.25mA) + (0.99995 × 0.7µA)
            ≈ 0.26µA + 0.7µA ≈ 1µA

With ADC sampling, LED, UART etc.: ~30-50µA total system
Goal achieved: <50µA ✓
```

## 3.2 DLE — Data Length Extension

### What it is
DLE (LE Data Length Extension) — introduced in BLE 4.2. Increases the maximum payload per LL packet from **27 bytes to 251 bytes**.

```
Without DLE:
  LL Payload = 27 bytes
  ATT header = 3 bytes
  GATT data  = 20 bytes per ATT packet
  For 500 bytes: need 25 ATT packets = 25 connection events minimum

With DLE (251 bytes):
  LL Payload = 251 bytes
  ATT header = 3 bytes
  GATT data  = 244 bytes per ATT packet
  For 500 bytes: need 3 ATT packets = 3 connection events
  
Throughput improvement: ~8x for large data transfers
```

### Code Example

```c
/* Request DLE from local controller */
uint8_t maxTxOctets = 251;   // Maximum TX PDU size
uint16_t maxTxTime  = 2120;  // Maximum TX time in µs (for 251 bytes at 1M PHY)

HCI_LE_SetDataLenCmd(connHandle, maxTxOctets, maxTxTime);

/* Handle DLE negotiation complete callback */
void BLE_processDLEEvent(hciEvt_BLEDataLenChange_t *pMsg) {
    LOG_INFO("DLE negotiated: MaxTxOctets=%d, MaxRxOctets=%d",
             pMsg->maxTxOctets, pMsg->maxRxOctets);
    /* Now update MTU to match: MTU = DLE payload - 4 bytes L2CAP header */
    uint16_t newMTU = pMsg->maxTxOctets - 4;  // 247 bytes
    ATT_UpdateMTU(connHandle, newMTU);
}
```

## 3.3 Packet Fragmentation and Flow Control

### L2CAP Fragmentation

```c
/* When ATT packet > LL PDU size, L2CAP fragments */
/* Example: 300-byte ATT packet, DLE = 251 bytes */

Fragment 1: [L2CAP header (4B) + 247B data] → LL PDU 251B ✓
Fragment 2: [53B data continuation]           → LL PDU 57B  ✓

/* L2CAP reassembly on receiver side: */
/* First fragment: PB flag = 10b (start of new PDU) */
/* Continuation:   PB flag = 01b (continuing PDU)   */
```

### ATT Flow Control

```c
/* ATT Write Command (no response) — no flow control */
/* Sender fires at will, no feedback from server */
/* Risk: server buffer overflow if sender is too fast */

/* Solution: Application-level credit system */
#define TX_CREDITS_MAX  4

typedef struct {
    uint16_t connHandle;
    uint8_t  txCredits;        // Available TX slots
    bool     pendingData;
} BLE_TxState_t;

/* When sending: */
void BLE_sendData(uint16_t connHandle, uint8_t *data, uint16_t len) {
    if (txState.txCredits == 0) {
        /* Queue data, wait for credit */
        enqueueData(data, len);
        return;
    }
    txState.txCredits--;
    GATT_WriteNoRsp(connHandle, data, len);
}

/* App-level ACK from server replenishes credits */
void BLE_onAckReceived(uint16_t connHandle) {
    txState.txCredits++;
    if (!isEmpty(txQueue)) {
        /* Send queued data */
        BLE_sendData(connHandle, dequeueData(), dataLen);
    }
}
```

## 3.4 Power Profiling

### How to profile BLE power

```
Tools used:
1. Nordic PPK2 (Power Profiler Kit) — hardware current measurement
2. Segger J-Link with SystemView — software task profiling
3. Logic analyzer — correlate GPIO signals with power spikes

Measurement setup:
- Remove any LEDs or debug peripherals
- Cut power rail, insert current probe
- Measure at 3.0V (coin cell simulation)

What to look for:
1. Idle current — should be MCU standby current
2. Advertising peak — radio Tx current × advertising duration
3. Connection event current — Tx+Rx for event duration
4. Wake-up current — transition from standby to active
5. Application processing current — CPU frequency × current

Profile output example:
  00.000ms: Wake from RTC        → 5.9mA (RTC IRQ, start ADC)
  00.200ms: ADC complete         → 4.2mA (process data)
  00.300ms: BLE Tx               → 6.1mA (send notification)
  00.400ms: BLE Rx               → 5.9mA (wait for ACK)
  00.450ms: Enter standby        → 0.0007mA (0.7µA)
  10000ms:  Next wake (repeat)
  
  Average: (6mA × 0.45ms + 0.7µA × 9999.55ms) / 10000ms ≈ 0.97µA
```

---

# PART 4: PROGRAMMING & RTOS

## 4.1 Embedded C Deep Dive

### Memory Layout

```
Flash (ROM):                RAM:
┌──────────────┐            ┌──────────────┐
│ .text         │            │ .data         │ ← initialized globals
│ (code)        │            ├──────────────┤
├──────────────┤            │ .bss          │ ← zero-initialized globals
│ .rodata       │            ├──────────────┤
│ (const data)  │            │ Heap          │ ← malloc()
├──────────────┤            │  ↓ grows down │
│ .data (init   │  ─copy→   ├──────────────┤
│  values)      │            │  ↑ grows up  │
└──────────────┘            │ Stack         │
                            └──────────────┘
```

### Volatile Keyword — Critical for Firmware

```c
/* Without volatile — WRONG in embedded */
uint8_t uartRxFlag = 0;
void UART_IRQHandler(void) { uartRxFlag = 1; }
void mainLoop(void) {
    while (!uartRxFlag) {} // Compiler may optimize to infinite loop!
    // Because compiler doesn't know IRQ can change uartRxFlag
}

/* With volatile — CORRECT */
volatile uint8_t uartRxFlag = 0;
// Compiler MUST read from memory each time, no caching in register
```

### Bit Manipulation (Critical for register-level firmware)

```c
/* Setting a bit: */
REG |= (1 << BIT_POS);

/* Clearing a bit: */
REG &= ~(1 << BIT_POS);

/* Toggling a bit: */
REG ^= (1 << BIT_POS);

/* Reading a bit: */
if (REG & (1 << BIT_POS)) { /* bit is set */ }

/* Real example — CC2340R5 GPIO control: */
#define GPIO_BASE    0x40022000
#define GPIO_DOUT    (*((volatile uint32_t *)(GPIO_BASE + 0x80)))
#define GPIO_DOUTSET (*((volatile uint32_t *)(GPIO_BASE + 0x90))) // Set pin high
#define GPIO_DOUTCLR (*((volatile uint32_t *)(GPIO_BASE + 0xA0))) // Set pin low

#define LED_PIN (1 << 6)  // DIO6

void LED_on(void)  { GPIO_DOUTSET = LED_PIN; }
void LED_off(void) { GPIO_DOUTCLR = LED_PIN; }
```

### Struct Packing (Critical for protocol frames)

```c
/* Packed struct for BLE advertising payload */
typedef struct __attribute__((packed)) {
    uint8_t  length;
    uint8_t  type;
    uint8_t  data[29];
} AdvPayload_t;
/* Without __packed: compiler adds padding for alignment */
/* With __packed: bytes are contiguous, safe for memcpy to radio buffer */

/* BLE uses little-endian by default */
/* Sending uint16_t over BLE: */
uint16_t value = 0x1234;
uint8_t buffer[2];
buffer[0] = value & 0xFF;        // 0x34 (LSB first — little endian)
buffer[1] = (value >> 8) & 0xFF; // 0x12

/* Or use: */
memcpy(buffer, &value, sizeof(value)); // Works on little-endian ARM Cortex-M
```

## 4.2 FreeRTOS — Deep Understanding

### Task States

```
         ┌──────────────────────────────────────────┐
         │              FreeRTOS States              │
         │                                           │
         │  RUNNING ←──────────────── READY         │
         │     │    (scheduler picks)    ↑           │
         │     │ (preemption or yield)   │           │
         │     ↓                         │           │
         │  BLOCKED ──── (event occurs) ─┘           │
         │  (waiting for                             │
         │   semaphore/queue/delay)                  │
         │                                           │
         │  SUSPENDED ←→ (vTaskSuspend/Resume)       │
         └──────────────────────────────────────────┘
```

### Semaphores vs Mutexes vs Queues

```c
/* SEMAPHORE — signaling between tasks/ISR */
SemaphoreHandle_t bleEventSem;
bleEventSem = xSemaphoreCreateBinary();

/* From ISR (BLE radio interrupt): */
void BLE_RadioISR(void) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(bleEventSem, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/* In BLE task: */
void BLE_Task(void *pvParam) {
    while (1) {
        xSemaphoreTake(bleEventSem, portMAX_DELAY); // Block until event
        BLE_processEvents();
    }
}

/* MUTEX — mutual exclusion, prevents concurrent access */
MutexHandle_t flashMutex;
flashMutex = xSemaphoreCreateMutex();

void Flash_write(uint32_t addr, uint8_t *data, uint16_t len) {
    xSemaphoreTake(flashMutex, portMAX_DELAY); // Lock
    /* Only one task writes flash at a time */
    NVS_write(addr, data, len);
    xSemaphoreGive(flashMutex); // Unlock
}

/* QUEUE — data passing between tasks */
QueueHandle_t sensorDataQueue;
sensorDataQueue = xQueueCreate(10, sizeof(SensorData_t)); // 10-item queue

/* Sensor task fills queue: */
void Sensor_Task(void *pvParam) {
    SensorData_t data;
    while (1) {
        readSensor(&data);
        xQueueSend(sensorDataQueue, &data, 0); // Don't block if full
        vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(1000)); // 1Hz sampling
    }
}

/* BLE task drains queue and sends notifications: */
void BLE_DataTask(void *pvParam) {
    SensorData_t data;
    while (1) {
        if (xQueueReceive(sensorDataQueue, &data, portMAX_DELAY) == pdTRUE) {
            Energy_notifyPower(activeConnHandle, data.power);
        }
    }
}
```

### Priority Inversion and Priority Inheritance

```
Problem (Priority Inversion):
  Task H (high priority) waits for mutex held by Task L (low priority)
  Task M (medium priority) preempts Task L, Task L can't release mutex
  Result: Task H is blocked by Task M — priority is INVERTED

Solution (Priority Inheritance):
  FreeRTOS mutex automatically raises Task L's priority to Task H's level
  Task L completes quickly, releases mutex, Task H can proceed
  Task L's priority returns to normal
  
  → Use xSemaphoreCreateMutex() NOT xSemaphoreCreateBinary() for shared resources
```

### Stack Overflow Detection

```c
/* Enable stack overflow checking in FreeRTOSConfig.h */
#define configCHECK_FOR_STACK_OVERFLOW  2  // Method 2: fill pattern check

/* Hook function called on stack overflow: */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    /* Log the task name and enter safe state */
    LOG_ERROR("Stack overflow in task: %s", pcTaskName);
    /* Trigger watchdog reset or safe shutdown */
    while(1);
}

/* Calculate stack requirements: */
/* Run system under maximum load, then check high water mark: */
UBaseType_t remaining = uxTaskGetStackHighWaterMark(NULL);
LOG_INFO("Stack remaining: %d words", remaining);
/* If remaining < 50 words, increase stack size */
```

## 4.3 State Machines in Firmware

### Why state machines are fundamental to BLE firmware

```c
/* BLE Connection State Machine */
typedef enum {
    BLE_STATE_IDLE,
    BLE_STATE_ADVERTISING,
    BLE_STATE_CONNECTING,
    BLE_STATE_CONNECTED,
    BLE_STATE_PAIRING,
    BLE_STATE_BONDED,
    BLE_STATE_DISCONNECTING,
    BLE_STATE_ERROR
} BLE_State_t;

static BLE_State_t currentState = BLE_STATE_IDLE;

/* State transition function */
void BLE_handleEvent(BLE_Event_t event) {
    switch (currentState) {
        case BLE_STATE_IDLE:
            if (event == BLE_EVT_START_ADV) {
                GapAdv_enable(advHandle, GAP_ADV_ENABLE_OPTIONS_USE_MAX, 0);
                currentState = BLE_STATE_ADVERTISING;
            }
            break;

        case BLE_STATE_ADVERTISING:
            if (event == BLE_EVT_CONNECTED) {
                currentState = BLE_STATE_CONNECTED;
                /* Start connection supervision */
                startSupervisionTimer();
            } else if (event == BLE_EVT_ADV_TIMEOUT) {
                /* No connection — go to deep sleep */
                currentState = BLE_STATE_IDLE;
                enterLowPowerMode();
            }
            break;

        case BLE_STATE_CONNECTED:
            if (event == BLE_EVT_PAIRING_REQ) {
                currentState = BLE_STATE_PAIRING;
            } else if (event == BLE_EVT_DISCONNECTED) {
                currentState = BLE_STATE_ADVERTISING;
                /* Restart advertising */
                GapAdv_enable(advHandle, GAP_ADV_ENABLE_OPTIONS_USE_MAX, 0);
            }
            break;

        /* ... other states */
    }
}
```

## 4.4 Interrupt-Driven Design

### Interrupt Priority Levels (ARM Cortex-M)

```c
/* ARM Cortex-M has configurable priority levels */
/* Higher number = lower priority (counterintuitive!) */
/* CC2340R5 / nRF52 typical setup: */

/* Priority 0 (highest): BLE radio interrupt — must never be delayed */
/* Priority 1: UART DMA complete */
/* Priority 2: SPI complete */
/* Priority 3 (lowest): Application/debug */

/* FreeRTOS: any ISR using RTOS API must have priority >= configMAX_SYSCALL_INTERRUPT_PRIORITY */
/* Typically: BLE radio = priority 0 (not using RTOS API) */
/*            Other ISRs = priority 3-7 (can use RTOS API) */

NVIC_SetPriority(BLE_IRQn,  0);  // BLE radio: highest, no RTOS calls
NVIC_SetPriority(UART_IRQn, 4);  // UART: can use xSemaphoreGiveFromISR
NVIC_SetPriority(SPI_IRQn,  4);  // SPI: can use xQueueSendFromISR
```

### ISR Design Rules

```c
/* Golden rules for ISRs: */
/* 1. Keep ISRs SHORT — do minimal work */
/* 2. Set a flag or give a semaphore, do work in task */
/* 3. NEVER call blocking functions (delay, printf, malloc) */
/* 4. Use volatile for shared variables */
/* 5. Disable interrupts only when absolutely necessary and for minimal time */

/* Good ISR: */
volatile bool adcComplete = false;
volatile uint16_t adcResult = 0;

void ADC_IRQHandler(void) {
    adcResult = ADC->RESULT;       // Read result
    adcComplete = true;             // Set flag
    /* Done — less than 10 instructions */
}

/* Main task processes the result: */
void ADC_Task(void *pvParam) {
    while (1) {
        if (adcComplete) {
            adcComplete = false;
            processADCResult(adcResult);
        }
        vTaskDelay(1);
    }
}
```

---

# PART 5: PERIPHERALS & MEMORY

## 5.1 SPI, I2C, UART — When to Use Which

### Comparison Table

| Protocol | Speed | Wires | Full Duplex | Multi-device | Use Case |
|---|---|---|---|---|---|
| **UART** | 115200–4Mbps | 2 (TX,RX) | Yes | No (1:1) | Debug console, GPS, BT module |
| **I2C** | 100kHz/400kHz/1MHz | 2 (SDA,SCL) | No | Yes (addr) | Sensors, OLED, EEPROM |
| **SPI** | 1–80MHz | 4 (MOSI,MISO,CLK,CS) | Yes | Yes (CS) | Flash, ADC, displays |

### SPI Driver (Bare Metal Example)

```c
/* Blocking SPI transfer — used for BMI160 IMU on STM32F407 */
uint8_t SPI_transfer(uint8_t data) {
    /* Wait until TX buffer empty */
    while (!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data;               // Send byte
    /* Wait until RX buffer not empty */
    while (!(SPI1->SR & SPI_SR_RXNE));
    return SPI1->DR;               // Return received byte
}

/* Read BMI160 register */
uint8_t BMI160_readReg(uint8_t regAddr) {
    uint8_t value;
    GPIO_DOUTCLR = CS_PIN;         // Assert CS (active low)
    SPI_transfer(regAddr | 0x80);  // Set MSB for read operation
    value = SPI_transfer(0x00);    // Dummy byte to clock out data
    GPIO_DOUTSET = CS_PIN;         // Deassert CS
    return value;
}

/* DMA-based SPI for non-blocking transfer (better for RTOS) */
void SPI_DMA_transfer(uint8_t *txBuf, uint8_t *rxBuf, uint16_t len) {
    /* Configure DMA channel for SPI TX */
    DMA2_Stream3->M0AR = (uint32_t)txBuf;
    DMA2_Stream3->NDTR = len;
    DMA2_Stream3->CR |= DMA_SxCR_EN;  // Start DMA

    /* Task blocks until DMA complete IRQ fires */
    xSemaphoreTake(spiDmaSem, portMAX_DELAY);
}
```

## 5.2 DMA — Direct Memory Access

### What it is and why it matters

Without DMA: CPU loads each byte from peripheral, stores to memory (CPU-bound)
With DMA: DMA controller transfers data autonomously, CPU is free for other work

```
Without DMA (SPI read 256 bytes):
  CPU: start SPI → wait → read byte → store → wait → read byte → store...
  256 iterations × ~10 cycles = 2560 cycles wasted waiting

With DMA:
  CPU: configure DMA → continue other work
  DMA: autonomously copies SPI RX FIFO → RAM buffer
  DMA IRQ fires when done → CPU processes 256 bytes at once
  CPU: 0 cycles wasted waiting
```

### DMA in BLE Context

```c
/* UART DMA for DLMS meter protocol reading */
/* Meter sends 248-byte DLMS frames at 9600 baud */
/* Time to receive 248 bytes at 9600 baud: ~260ms */
/* Without DMA: CPU polls UART for 260ms — can't run BLE! */
/* With DMA: CPU programs DMA, handles BLE, DMA ISR fires after 260ms */

void DLMS_startReceive(void) {
    /* Configure DMA for UART4 RX */
    DMA1_Stream2->M0AR = (uint32_t)dlmsRxBuffer;
    DMA1_Stream2->NDTR = DLMS_FRAME_SIZE;
    DMA1_Stream2->CR = DMA_SxCR_CHSEL_4 |    // Channel 4 = UART4
                       DMA_SxCR_PL_HIGH |      // High priority
                       DMA_SxCR_MSIZE_BYTE |
                       DMA_SxCR_PSIZE_BYTE |
                       DMA_SxCR_MINC |         // Memory increment
                       DMA_SxCR_TCIE |         // Transfer complete interrupt
                       DMA_SxCR_EN;            // Enable DMA
}

void DMA1_Stream2_IRQHandler(void) {
    DMA1->LIFCR |= DMA_LIFCR_CTCIF2; // Clear interrupt flag
    BaseType_t xHighPriTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(dlmsRxSem, &xHighPriTaskWoken);
    portYIELD_FROM_ISR(xHighPriTaskWoken);
}
```

## 5.3 Watchdog Timer

### Why it's critical in embedded systems

```c
/* Hardware watchdog prevents system lockup */
/* If firmware hangs, watchdog resets the MCU */

/* CC2340R5 Watchdog configuration */
void WDT_init(void) {
    /* Set timeout: 5 seconds */
    WDT->LOAD = 5000 * (SystemCoreClock / 1000);
    /* Enable watchdog with reset on timeout */
    WDT->CTL = WDT_CTL_INTEN | WDT_CTL_RESEN;
    /* Enable lock to prevent accidental disable */
    WDT->LOCK = WDT_LOCK_VALUE;
}

/* Must be called within 5 seconds from any task */
void WDT_feed(void) {
    WDT->LOCK = WDT_UNLOCK_VALUE;
    WDT->LOAD = 5000 * (SystemCoreClock / 1000);
    WDT->LOCK = WDT_LOCK_VALUE;
}

/* In each main task loop: */
void BLE_Task(void *pvParam) {
    while (1) {
        WDT_feed();  // Feed watchdog at top of loop
        xSemaphoreTake(bleEventSem, pdMS_TO_TICKS(1000));
        BLE_processEvents();
    }
}
```

## 5.4 Flash Memory — LittleFS, NVS, EEPROM Emulation

### Flash Write Characteristics

```
Flash properties that affect firmware design:
1. ERASE before WRITE — can only write 1→0 (set bits), not 0→1
2. ERASE is by PAGE (typically 4KB) — can't erase individual bytes
3. WRITE ENDURANCE — ~10,000–100,000 erase cycles per page
4. WRITE is SLOW — flash write ~200µs, erase ~50ms per page
5. POWER-FAIL SAFETY — write must be atomic or use journaling
```

### NVS (Non-Volatile Storage) on CC2340R5

```c
/* NVS provides a key-value store with wear leveling */
#include <ti/drivers/NVS.h>

typedef struct {
    uint8_t  ltk[16];
    uint8_t  irk[16];
    uint8_t  csrk[16];
    uint8_t  peerAddr[6];
    uint8_t  addrType;
    uint16_t encKeySize;
} BondRecord_t;

/* Write bond record */
int8_t Bond_save(uint8_t bondIndex, BondRecord_t *record) {
    NVS_Handle nvsHandle;
    NVS_Params nvsParams;
    NVS_Params_init(&nvsParams);

    nvsHandle = NVS_open(BOND_NVS_REGION, &nvsParams);
    if (!nvsHandle) return -1;

    uint32_t offset = bondIndex * sizeof(BondRecord_t);
    int_fast16_t result = NVS_write(nvsHandle, offset,
                                     record, sizeof(BondRecord_t),
                                     NVS_WRITE_ERASE | NVS_WRITE_POST_VERIFY);
    NVS_close(nvsHandle);
    return (result == NVS_STATUS_SUCCESS) ? 0 : -1;
}
```

### LittleFS (Used in your Automotive OTA project)

```c
/* LittleFS: Power-fail-safe filesystem for embedded flash */
/* Key feature: if power cut during write, filesystem remains consistent */

/* Configuration */
const struct lfs_config cfg = {
    .read  = lfs_flash_read,     // Platform flash read function
    .prog  = lfs_flash_prog,     // Platform flash write function
    .erase = lfs_flash_erase,    // Platform flash erase function
    .sync  = lfs_flash_sync,

    .read_size   = 16,
    .prog_size   = 16,
    .block_size  = 4096,         // Flash page size
    .block_count = 64,           // 64 × 4KB = 256KB filesystem
    .cache_size  = 16,
    .lookahead_size = 16,
    .block_cycles = 500,         // Wear leveling: move block after 500 erases
};

/* OTA: Write new firmware to filesystem */
void OTA_writeFirmware(const uint8_t *fw, size_t len) {
    lfs_t lfs;
    lfs_mount(&lfs, &cfg);

    lfs_file_t file;
    lfs_file_open(&lfs, &file, "firmware.bin",
                  LFS_O_WRONLY | LFS_O_CREAT | LFS_O_TRUNC);
    lfs_file_write(&lfs, &file, fw, len);
    lfs_file_close(&lfs, &file);

    lfs_unmount(&lfs);
    /* Power-fail safe: if power cut here, old firmware still intact */
    /* Swap flag set only after complete write + verification */
}
```

---

# PART 6: BOOTLOADERS & SECURITY

## 6.1 Custom Bootloader Design

### What a Bootloader Does

```
Power ON
    ↓
Bootloader starts (runs from fixed flash address, e.g., 0x00000000)
    ↓
Check: Is there a pending OTA image?
    ↓ YES                          ↓ NO
Verify OTA image (SHA-256)     Jump to Application (e.g., 0x00010000)
    ↓                              ↓
VALID → Copy to active slot     Application runs
    ↓
Erase old image
    ↓
Set boot flag to "run new"
    ↓
Reset MCU → Boot new firmware
```

### Dual-Bank Flash Layout (CC2340R5 / 256KB Flash)

```
Flash Map:
0x00000000 ├──────────────────────┤
           │   Bootloader          │  32KB
           │   (never overwritten) │
0x00008000 ├──────────────────────┤
           │   Boot Config Page    │  4KB
           │   (A/B flags, version)│
0x00009000 ├──────────────────────┤
           │   Bank A (ACTIVE)     │  96KB
           │   Running Firmware    │
0x00021000 ├──────────────────────┤
           │   Bank B (UPDATE)     │  96KB
           │   OTA Image received  │
0x00039000 ├──────────────────────┤
           │   NVS (Bond keys etc) │  28KB
0x00040000 └──────────────────────┘
```

### Boot Configuration Structure

```c
/* Boot config stored in dedicated flash page */
typedef struct {
    uint32_t magic;           // 0xB007C0DE — valid config marker
    uint8_t  activeBank;      // 0 = Bank A, 1 = Bank B
    uint8_t  updatePending;   // 1 = new image in inactive bank
    uint8_t  bootAttempts;    // Incremented each boot, reset by app
    uint8_t  rollbackEnabled; // 1 = rollback if bootAttempts > 3
    uint32_t fwVersionActive; // e.g., 0x00010203 = v1.2.3
    uint32_t fwVersionUpdate; // Version of pending OTA image
    uint8_t  sha256Active[32]; // SHA-256 of running firmware
    uint8_t  sha256Update[32]; // SHA-256 of pending OTA image
    uint32_t crc32;           // CRC32 of this struct (self-integrity)
} BootConfig_t;

/* Bootloader main logic */
void Bootloader_main(void) {
    BootConfig_t cfg;
    Flash_read(BOOT_CONFIG_ADDR, &cfg, sizeof(cfg));

    /* Validate boot config */
    if (cfg.magic != 0xB007C0DE || !verifyConfigCRC(&cfg)) {
        /* Corrupt config — run Bank A (factory default) */
        jumpToApplication(BANK_A_ADDR);
        return;
    }

    /* Check if update is pending */
    if (cfg.updatePending) {
        /* Verify SHA-256 of update image */
        if (SHA256_verify(BANK_B_ADDR, cfg.fwVersionUpdate, cfg.sha256Update)) {
            /* Valid — swap banks */
            cfg.activeBank = 1 - cfg.activeBank;
            cfg.updatePending = 0;
            cfg.bootAttempts = 0;
            Flash_write(BOOT_CONFIG_ADDR, &cfg, sizeof(cfg));
        } else {
            /* Invalid image — clear update flag */
            cfg.updatePending = 0;
            Flash_write(BOOT_CONFIG_ADDR, &cfg, sizeof(cfg));
        }
    }

    /* Rollback check */
    cfg.bootAttempts++;
    Flash_write(BOOT_CONFIG_ADDR, &cfg, sizeof(cfg));

    if (cfg.bootAttempts > 3) {
        /* Too many failed boots — rollback to other bank */
        cfg.activeBank = 1 - cfg.activeBank;
        cfg.bootAttempts = 0;
        Flash_write(BOOT_CONFIG_ADDR, &cfg, sizeof(cfg));
    }

    /* Jump to active bank */
    uint32_t appAddr = (cfg.activeBank == 0) ? BANK_A_ADDR : BANK_B_ADDR;
    jumpToApplication(appAddr);
}
```

## 6.2 MCUboot

### What it is
MCUboot is an **open-source, standards-based secure bootloader** for Cortex-M devices. Used in Zephyr RTOS, Apache Mynewt, and many RTOS platforms.

### MCUboot Slot Layout

```
Primary Slot (runs from here)
Secondary Slot (receives OTA image)
Scratch Area (for swap operation)

Image Trailer (at end of each slot):
┌─────────────────────┐
│ Magic value         │ 16 bytes
├─────────────────────┤
│ Image OK flag       │ 1 byte (set by app after successful boot)
├─────────────────────┤
│ Copy Done flag      │ 1 byte
├─────────────────────┤
│ Swap Type           │ 1 byte (NONE/TEST/PERM/REVERT)
└─────────────────────┘
```

### OTA Update Flow with MCUboot

```
1. OTA client receives new firmware → writes to Secondary Slot
2. OTA client verifies SHA-256 of secondary slot
3. OTA client sets "SWAP_TYPE_TEST" in image trailer
4. Device resets
5. MCUboot sees pending test update
6. MCUboot verifies image signature (if secure boot enabled)
7. MCUboot swaps Primary ↔ Secondary (3-way swap using scratch)
8. New firmware boots
9. If app marks Image OK → permanent upgrade
10. If app doesn't mark OK (crash) → MCUboot reverts on next boot
```

## 6.3 AES-128/256 and SHA-256

### AES-128 OTA Encryption

```c
/* OTA firmware is encrypted with AES-128-CBC before transmission */
/* This prevents firmware theft/reverse engineering over BLE air interface */

#include <tinycrypt/aes.h>
#include <tinycrypt/cbc_mode.h>

#define AES_KEY_SIZE  16  // AES-128
static const uint8_t ota_aes_key[AES_KEY_SIZE] = {
    /* Pre-shared key, stored in device secure storage / OTP */
    0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
    0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C
};

/* Decrypt OTA chunk received over BLE */
int OTA_decryptChunk(uint8_t *encData, uint8_t *iv,
                      uint8_t *plainData, uint16_t len) {
    struct tc_aes_key_sched_struct sched;
    if (tc_aes128_set_decrypt_key(&sched, ota_aes_key) != TC_CRYPTO_SUCCESS)
        return -1;

    if (tc_cbc_mode_decrypt(plainData, len,
                             encData, len,
                             iv, &sched) != TC_CRYPTO_SUCCESS)
        return -1;

    return 0;
}

/* SHA-256 verification of complete firmware image */
int OTA_verifyImage(uint32_t flashAddr, uint32_t len, uint8_t *expectedHash) {
    struct tc_sha256_state_struct sha;
    tc_sha256_init(&sha);

    /* Process in 256-byte chunks to limit RAM usage */
    uint8_t chunk[256];
    uint32_t remaining = len;
    uint32_t offset = 0;

    while (remaining > 0) {
        uint16_t chunkSize = MIN(remaining, sizeof(chunk));
        Flash_read(flashAddr + offset, chunk, chunkSize);
        tc_sha256_update(&sha, chunk, chunkSize);
        offset += chunkSize;
        remaining -= chunkSize;
    }

    uint8_t computedHash[32];
    tc_sha256_final(computedHash, &sha);

    return (memcmp(computedHash, expectedHash, 32) == 0) ? 0 : -1;
}
```

### CRC32 for Quick Integrity Checks

```c
/* CRC32 is faster than SHA-256, used for quick boot-time checks */
uint32_t CRC32_compute(const uint8_t *data, uint32_t len) {
    uint32_t crc = 0xFFFFFFFF;
    for (uint32_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            crc = (crc >> 1) ^ (0xEDB88320 * (crc & 1));
        }
    }
    return ~crc;
}
/* SHA-256 for security (can't be forged), CRC32 for corruption detection */
```

---

# PART 7: EMBEDDED LINUX & AUTOMOTIVE

## 7.1 U-Boot and A/B Partition Scheme

### What U-Boot is
U-Boot (Das U-Boot) is the de-facto standard **bootloader for embedded Linux** systems. It handles hardware init, then loads and boots the Linux kernel.

### U-Boot Boot Sequence

```
Power ON → ROM bootcode → SPL (Secondary Program Loader)
    ↓
U-Boot proper loads (from eMMC/NAND/SPI flash)
    ↓
U-Boot initializes DDR RAM, network, storage
    ↓
U-Boot reads environment variables
    ↓
Selects kernel image (A or B partition)
    ↓
Loads kernel to RAM: tftp / mmc load
    ↓
Sets kernel boot args (bootargs env var)
    ↓
Boots kernel: bootz / booti command
```

### A/B Partition Scheme on BeagleBone Black

```
SD Card / eMMC Layout:
┌─────────────────┐
│ SPL + U-Boot    │  Raw sectors (not filesystem)
├─────────────────┤
│ Boot Config     │  U-Boot env (bootcount, upgrade_available, boot_part)
├─────────────────┤
│ Partition A     │  Kernel + DTB + RootFS (ext4)
│ (mmcblk0p2)     │  Active/fallback
├─────────────────┤
│ Partition B     │  Kernel + DTB + RootFS (ext4)
│ (mmcblk0p3)     │  OTA target
└─────────────────┘
```

### U-Boot Environment Variables for A/B (What You Implemented)

```bash
# U-Boot environment for automotive OTA
setenv bootcount 0
setenv upgrade_available 0
setenv boot_part a

# Boot script (bootcmd):
setenv bootcmd '
  if test ${upgrade_available} = 1; then
    if test ${bootcount} > 3; then
      echo "Too many failed boots, rolling back";
      setenv boot_part ${fallback_part};
      setenv upgrade_available 0;
      setenv bootcount 0;
      saveenv;
    fi;
  fi;
  
  setexpr bootcount ${bootcount} + 1;
  saveenv;
  
  if test ${boot_part} = a; then
    setenv bootargs root=/dev/mmcblk0p2 rw console=ttyS0,115200;
    load mmc 0:2 ${kernel_addr_r} /boot/zImage;
    load mmc 0:2 ${fdt_addr_r} /boot/am335x-boneblack.dtb;
  else;
    setenv bootargs root=/dev/mmcblk0p3 rw console=ttyS0,115200;
    load mmc 0:3 ${kernel_addr_r} /boot/zImage;
    load mmc 0:3 ${fdt_addr_r} /boot/am335x-boneblack.dtb;
  fi;
  bootz ${kernel_addr_r} - ${fdt_addr_r};
'
saveenv
```

### Rollback Mechanism

```bash
# In Linux userspace (run after successful boot validation):
#!/bin/bash
# /usr/bin/ota_healthcheck.sh — run at startup

# Verify critical services are running
systemctl is-active --quiet can-bus-daemon || exit 1
systemctl is-active --quiet diagnostic-agent || exit 1

# All good — clear upgrade flag and reset boot counter
fw_setenv upgrade_available 0
fw_setenv bootcount 0
echo "OTA: Health check passed, boot committed"
```

## 7.2 Device Tree

### What it is
Device Tree is a data structure that describes hardware to the Linux kernel. Instead of hard-coding hardware addresses in the kernel, the bootloader passes a DTB (Device Tree Blob) to the kernel.

```
/* Device Tree Source (.dts) example for BeagleBone Black */
/* Adding CAN bus node for automotive OTA communication */

/ {
    compatible = "ti,am335x-bone-black", "ti,am335x-bone", "ti,am33xx";

    /* CAN bus for automotive communication */
    &dcan1 {
        status = "okay";
        pinctrl-names = "default";
        pinctrl-0 = <&dcan1_pins>;
    };

    /* UART for OTA debug console */
    &uart0 {
        status = "okay";
        pinctrl-0 = <&uart0_pins>;
    };

    /* SPI flash for boot config */
    &spi0 {
        status = "okay";
        flash: w25q64@0 {
            compatible = "winbond,w25q64", "jedec,spi-nor";
            reg = <0>;
            spi-max-frequency = <24000000>;
            partitions {
                compatible = "fixed-partitions";
                #address-cells = <1>;
                #size-cells = <1>;
                partition@0 {
                    label = "boot-config";
                    reg = <0x0 0x10000>;
                };
            };
        };
    };
};
```

## 7.3 Boot Time Optimization (8.5s → 3.2s)

### What you did and why it matters

```
Original boot sequence (8.5s):
  U-Boot:              1.2s  (serial output, delays)
  Kernel decompression: 0.8s
  Kernel init:         1.5s
  Root filesystem:     0.5s  (ext4 check)
  Systemd startup:     4.5s  (sequential service start)
  Total:               8.5s

Optimized (3.2s):
  U-Boot:              0.6s  (removed delays, reduced verbosity)
  Kernel decompression: 0.5s  (precompressed LZ4 instead of gzip)
  Kernel init:         0.8s  (disabled unused drivers)
  Root filesystem:     0.3s  (squashfs read-only for rootfs)
  Systemd startup:     1.0s  (parallel + deferred services)
  Total:               3.2s
```

### Specific Optimizations

```bash
# 1. U-Boot: Remove boot delay
setenv bootdelay 0
setenv silent 1

# 2. Kernel: Disable unused drivers in config
# CONFIG_USB_GADGET=n
# CONFIG_SOUND=n
# CONFIG_FB=n (if no framebuffer needed)

# 3. Kernel cmdline: faster init
bootargs="... quiet loglevel=3 rd.systemd.show_status=false"

# 4. Systemd: Analyze and defer non-critical services
systemd-analyze blame        # See slowest services
systemd-analyze critical-chain  # See boot-critical path

# 5. Parallel service start (already default in systemd)
# But ensure services don't have unnecessary After= dependencies

# 6. Deferred driver loading — don't load USB, Wi-Fi at boot if not needed
# Use systemd .service with Type=oneshot and RemainAfterExit=yes
# triggered by udev or timer

# 7. Flash read optimization: Use LZ4 for kernel compression
# LZ4 decompresses 2x faster than gzip with similar ratio
```

## 7.4 Mender OTA Framework

### Architecture

```
Cloud (Mender Server)
        ↓  HTTPS (TLS)
Mender Client (runs on BeagleBone)
        ↓
Artifact download + verification
        ↓
Write to inactive partition (B if running A)
        ↓
Set upgrade_available=1 in U-Boot env
        ↓
Reboot → U-Boot boots new partition
        ↓
Mender client checks system health
        ↓
Mark update as successful (or rollback)
```

### Mender Artifact Structure

```
.mmar (Mender Artifact):
├── version          (format version)
├── header.tar.gz
│   ├── header-info  (artifact name, device types)
│   └── headers/0000/
│       ├── type-info    (rootfs-image)
│       ├── meta-data    (SHA256, size)
│       └── signatures/  (if signed)
└── data/0000.tar.gz     (actual rootfs image)
```

---

# PART 8: DEVELOPMENT TOOLS

## 8.1 JTAG and GDB Debugging

### Debug Connection

```
Host PC (GDB) ←→ J-Link probe ←→ JTAG/SWD pins ←→ MCU

JTAG pins: TDI, TDO, TCK, TMS, TRST
SWD pins: SWDIO, SWDCLK (only 2 pins, more common on small MCUs)
```

### GDB Commands for Firmware Debugging

```bash
# Connect to J-Link GDB server
arm-none-eabi-gdb firmware.elf
(gdb) target remote localhost:2331   # J-Link GDB server

# Core debugging commands
(gdb) monitor reset halt     # Reset and halt MCU
(gdb) load                   # Flash firmware
(gdb) break main             # Set breakpoint at main()
(gdb) continue               # Run until breakpoint
(gdb) next                   # Step over
(gdb) step                   # Step into
(gdb) print variable_name   # Print variable value
(gdb) x/10x 0x20000000      # Examine memory: 10 hex words at address

# Debugging a crash: read fault registers
(gdb) info registers         # All CPU registers
(gdb) print/x $pc            # Program Counter (where crash happened)
(gdb) print/x $lr            # Link Register (who called the crashed function)
(gdb) x/1x $sp               # Stack pointer

# Hard fault analysis (ARM Cortex-M specific)
(gdb) print/x *(0xE000ED28)  # CFSR: Configurable Fault Status Register
(gdb) print/x *(0xE000ED2C)  # HFSR: Hard Fault Status Register
(gdb) print/x *(0xE000ED34)  # MMFAR: MemManage Fault Address Register
(gdb) print/x *(0xE000ED38)  # BFAR: BusFault Address Register
```

### Hard Fault Handler for Root Cause Analysis

```c
/* Custom hard fault handler — dumps context before reset */
void HardFault_Handler(void) {
    /* Get stack pointer */
    __asm volatile (
        "TST LR, #4           \n"
        "ITE EQ               \n"
        "MRSEQ R0, MSP        \n"  // Main stack pointer
        "MRSNE R0, PSP        \n"  // Process stack pointer
        "B hardFaultDump      \n"
    );
}

void hardFaultDump(uint32_t *stackPtr) {
    uint32_t r0  = stackPtr[0];
    uint32_t r1  = stackPtr[1];
    uint32_t r2  = stackPtr[2];
    uint32_t r3  = stackPtr[3];
    uint32_t r12 = stackPtr[4];
    uint32_t lr  = stackPtr[5];  // Link Register
    uint32_t pc  = stackPtr[6];  // Program Counter (crash address)
    uint32_t psr = stackPtr[7];  // Program Status Register

    /* Log to UART before reset */
    UART_printf("HARD FAULT at PC=0x%08X LR=0x%08X\r\n", pc, lr);
    UART_printf("CFSR=0x%08X HFSR=0x%08X\r\n",
                SCB->CFSR, SCB->HFSR);

    /* Save to flash for post-mortem */
    FlashLog_saveCrashDump(pc, lr, SCB->CFSR, SCB->HFSR);

    /* Reset MCU */
    NVIC_SystemReset();
}
```

## 8.2 Ellisys BLE Analyzer / Wireshark

### How BLE packet capture works

```
Ellisys BLE Analyzer:
- Hardware sniffer that passively captures all BLE traffic
- Can capture on all 40 BLE channels simultaneously
- Decodes all layers: LL, L2CAP, ATT, GATT, SMP
- Can decrypt if you provide the LTK or PIN

Workflow for debugging BLE issues:
1. Start capture before pairing (to capture LTK for decryption)
2. Reproduce the issue
3. Stop capture and analyze:
   - Check connection event timing (are events missed?)
   - Check RSSI values (signal quality)
   - Look for LL NACK/retransmissions (packet errors)
   - Check connection parameter updates
   - Look for ATT errors (access denied, value not found)
   - Examine SMP messages for pairing failures
```

### Common BLE Issues Found via Analyzer

```
Issue 1: Connection drops (Supervision Timeout)
  Symptom: LL_TERMINATE_IND with reason 0x08 (Connection Timeout)
  Root cause: supervision timeout too short for long connection intervals
  Fix: timeout > (1 + latency) * interval * 2

Issue 2: Pairing failure
  Symptom: SMP_PAIRING_FAILED PDU in capture
  Reason codes: 0x05=Pairing Not Supported, 0x09=Confirm Value Failed,
                0x0F=Repeated Attempts
  Root cause: mismatched IO capabilities or repeated failed attempts

Issue 3: ATT timeout
  Symptom: Application-level timeout waiting for ATT_WRITE_RSP
  Root cause: server busy, ATT request queue full
  Fix: Implement ATT request queuing with retry logic

Issue 4: Throughput degradation
  Symptom: Slow data transfer despite short connection interval
  Root cause: Not using DLE, small MTU, ATT request-response ping-pong
  Fix: Enable DLE, negotiate max MTU, use Write Without Response for streaming
```

---

# PART 9: PLATFORMS DEEP DIVE

## 9.1 TI CC2340R5

### Architecture Overview

```
CC2340R5 Block Diagram:
┌────────────────────────────────────────┐
│              CC2340R5                  │
│                                        │
│  ARM Cortex-M0+ @ 48MHz               │
│  ┌──────────┐  ┌──────────────────┐  │
│  │  256KB   │  │   BLE 5.3        │  │
│  │  Flash   │  │   Controller     │  │
│  ├──────────┤  │   (2.4GHz radio) │  │
│  │  24KB    │  └──────────────────┘  │
│  │  SRAM    │                        │
│  └──────────┘  ┌──────────────────┐  │
│                │   Peripherals:   │  │
│  Low Power:    │  2×UART, 2×SPI,  │  │
│  Standby 0.7µA │  I2C, ADC, Timer │  │
│  Shutdown 25nA │  RTC, Watchdog   │  │
└────────────────────────────────────────┘
```

### Power Modes

```c
/* CC2340R5 Power Modes */
/* Mode 0 (Active):    Cortex-M0+ running, all peripherals */
/* Mode 1 (Idle):      CPU halted, peripherals running */
/* Mode 2 (Standby):   Only RTC, RAM retained — 0.7µA */
/* Mode 3 (Shutdown):  Everything off — 25nA */

/* Enter Standby mode (deepest sleep with BLE wakeup) */
void enterStandby(void) {
    /* Configure RTC wakeup for next connection event */
    uint32_t wakeupTick = RTC_getCurrentTick() + 
                          CONNECTION_INTERVAL_TICKS - WAKEUP_MARGIN_TICKS;
    RTC_setWakeup(wakeupTick);

    /* Ensure flash is flushed */
    FlashCtl_waitForLastOperation();

    /* Enter standby — MCU halts here */
    Power_sleep(PowerCC23X0_STANDBY);
    /* Execution resumes here after wakeup */
}
```

## 9.2 Nordic nRF52832 / nRF52840

### SoftDevice Architecture (vs CC2340R5 SimpleLink SDK)

```
nRF52 BLE Architecture:
┌────────────────────────────────┐
│  Application Code              │  Your firmware
│  (runs in S132 SoftDevice API) │
├────────────────────────────────┤
│  S132 SoftDevice               │  Nordic's closed-source BLE stack
│  (sits in lower flash/RAM)     │  Reserves ~100KB flash, ~24KB RAM
├────────────────────────────────┤
│  nRF52832 Hardware             │
└────────────────────────────────┘

Key difference from CC2340R5:
- CC2340R5: Open protocol stack (TI-RTOS + BLE controller)
- nRF52832: SoftDevice (closed, pre-validated BLE host+controller)
- nRF52840: Adds USB, larger flash, more RAM vs nRF52832
```

### SoftDevice API Example (from your Araciv work)

```c
/* Custom GATT Service for IMU data streaming (Vicara project) */
/* nRF52832 + Nordic S132 SoftDevice */

#include "ble.h"
#include "ble_srv_common.h"

#define IMU_SERVICE_UUID        0x1523
#define IMU_QUATERNION_CHAR_UUID 0x1524
#define IMU_ACCEL_CHAR_UUID     0x1525

typedef struct __attribute__((packed)) {
    int16_t w;  // Quaternion W × 32767
    int16_t x;  // Quaternion X × 32767
    int16_t y;
    int16_t z;
} IMU_Quaternion_t;  // 8 bytes

/* Send IMU notification at 20Hz over BLE */
void IMU_notifyQuaternion(uint16_t connHandle, IMU_Quaternion_t *quat) {
    if (connHandle == BLE_CONN_HANDLE_INVALID) return;

    ble_gatts_hvx_params_t params = {
        .handle = imuQuatCharHandle.value_handle,
        .type   = BLE_GATT_HVX_NOTIFICATION,
        .offset = 0,
        .p_len  = &(uint16_t){sizeof(IMU_Quaternion_t)},
        .p_data = (uint8_t *)quat
    };

    sd_ble_gatts_hvx(connHandle, &params);
}
```

## 9.3 ESP32-C3

### Key Features Relevant to Your Work

```
ESP32-C3 (RISC-V architecture, not ARM):
- CPU: RISC-V single-core @ 160MHz
- Memory: 400KB SRAM, 384KB ROM
- Wireless: Wi-Fi 802.11 b/g/n + BLE 5.0 (single die)
- Flash: External SPI Flash (typically 4MB)
- Key advantage over nRF52: Wi-Fi + BLE on same SoC

Your Araciv work: Migrated nRF52832 → ESP32-C3
Reason: ESP32-C3 adds Wi-Fi + OTA over Wi-Fi for 30% lower BOM cost
```

### Wi-Fi Provisioning over BLE (What You Built)

```c
/* BLE-based Wi-Fi provisioning for ESP32-C3 */
/* Phone connects via BLE, sends Wi-Fi credentials encrypted */
/* ESP32-C3 saves credentials to NVS, connects to Wi-Fi */

/* Custom provision GATT service */
#define PROV_SERVICE_UUID    "12345678-1234-1234-1234-123456789012"
#define SSID_CHAR_UUID       "12345678-1234-1234-1234-123456789013"
#define PASSWORD_CHAR_UUID   "12345678-1234-1234-1234-123456789014"
#define STATUS_CHAR_UUID     "12345678-1234-1234-1234-123456789015"

/* Encrypted credential transfer */
typedef struct __attribute__((packed)) {
    uint8_t  iv[16];       // AES initialization vector
    uint8_t  encData[80];  // AES-128-CBC encrypted {ssid, password}
    uint8_t  hmac[16];     // HMAC-MD5 for integrity
} ProvCredentials_t;

static void onCredentialsWrite(ble_gatts_evt_write_t *write_evt) {
    ProvCredentials_t *creds = (ProvCredentials_t *)write_evt->data;

    /* Verify HMAC */
    if (!HMAC_verify(creds->encData, 80, creds->hmac)) {
        sendProvStatus(PROV_STATUS_AUTH_FAILED);
        return;
    }

    /* Decrypt credentials */
    uint8_t plain[80];
    AES_CBC_decrypt(creds->encData, creds->iv, plain, 80, prov_aes_key);

    /* Save to NVS */
    nvs_handle_t nvs;
    nvs_open("wifi_creds", NVS_READWRITE, &nvs);
    nvs_set_str(nvs, "ssid",     (char *)plain);
    nvs_set_str(nvs, "password", (char *)(plain + 32));
    nvs_commit(nvs);
    nvs_close(nvs);

    /* Disconnect BLE, connect Wi-Fi */
    sendProvStatus(PROV_STATUS_SUCCESS);
    vTaskDelay(pdMS_TO_TICKS(500));
    esp_wifi_connect();
}
```

---

# PART 10: WORK EXPERIENCE DEEP DIVES

## 10.1 Tata Technologies — Automotive OTA Pipeline

### CAN Bus OTA Delivery

```c
/* Delivering firmware over CAN bus — ISO 15765-2 (CAN-TP) */
/* CAN has 8-byte max payload, need to fragment larger OTA data */

/* CAN-TP (Transport Protocol) frame types: */
/* Single Frame (SF):  payload ≤ 7 bytes */
/* First Frame (FF):   start of multi-frame (size in first 12 bits) */
/* Consecutive Frame (CF): continuation data */
/* Flow Control (FC):  receiver controls pacing */

typedef enum {
    CANTP_SINGLE_FRAME       = 0x0,
    CANTP_FIRST_FRAME        = 0x1,
    CANTP_CONSECUTIVE_FRAME  = 0x2,
    CANTP_FLOW_CONTROL       = 0x3
} CANTP_FrameType_t;

/* Send OTA data over CAN-TP */
void CANTP_sendMultiFrame(uint32_t canId, uint8_t *data, uint16_t totalLen) {
    /* First Frame */
    uint8_t ff[8];
    ff[0] = (CANTP_FIRST_FRAME << 4) | ((totalLen >> 8) & 0x0F);
    ff[1] = totalLen & 0xFF;
    memcpy(&ff[2], data, 6);
    CAN_send(canId, ff, 8);

    /* Wait for Flow Control from ECU */
    waitForFlowControl();

    /* Send Consecutive Frames */
    uint8_t seqNum = 1;
    uint16_t offset = 6;
    while (offset < totalLen) {
        uint8_t cf[8] = {0};
        cf[0] = (CANTP_CONSECUTIVE_FRAME << 4) | (seqNum & 0x0F);
        uint16_t chunkLen = MIN(7, totalLen - offset);
        memcpy(&cf[1], data + offset, chunkLen);
        CAN_send(canId, cf, 8);
        seqNum++;
        offset += 7;
    }
}
```

### BeagleBone Black — Boot Time Debug Session

```bash
# How you debugged boot time on BeagleBone Black using UART console

# Connect UART to PC (3.3V UART on J1 header):
# Pin 1: GND, Pin 4: RX (PC→BBB), Pin 5: TX (BBB→PC)
screen /dev/ttyUSB0 115200

# Kernel boot log analysis:
dmesg | grep "initcall" | sort -t' ' -k1 -n  # Slowest init calls

# Systemd analysis:
systemd-analyze                    # Total boot time
systemd-analyze blame              # Slowest services
systemd-analyze critical-chain     # Dependency chain

# Found slow service example:
#   3.423s dev-mmcblk0p2.device    ← eMMC detection delay
#   2.1s   networking.service      ← DHCP timeout
#   1.8s   systemd-fsck@.service   ← filesystem check

# Fix 1: Add rootwait to kernel cmdline (wait for eMMC)
# Fix 2: Use systemd-networkd with link-local timeout
# Fix 3: Use squashfs (read-only, no fsck needed)
```

## 10.2 Tinymesh Radiocraft — Smart Meter (500+ Deployments)

### Production Test Firmware (12 min → 4 min)

```c
/* Production test firmware — tests all hardware quickly */
/* Original: manual BLE pairing test, manual signal check = 12 min */
/* Optimized: automated test sequence = 4 min */

typedef enum {
    TEST_PASS = 0,
    TEST_FAIL = 1,
    TEST_SKIP = 2
} TestResult_t;

typedef struct {
    const char *name;
    TestResult_t (*run)(void);
    uint32_t timeoutMs;
} Test_t;

TestResult_t test_crystal(void) {
    /* Verify 32kHz crystal is running within ±50ppm */
    uint32_t rtcBefore = RTC_getTick();
    delay_ms_hclk(1000);  // 1 second using HCLK
    uint32_t rtcAfter = RTC_getTick();
    uint32_t rtcDelta = rtcAfter - rtcBefore;
    /* 32768 ticks/sec ± 50ppm = 32768 ± 1.6 ticks */
    return (rtcDelta >= 32766 && rtcDelta <= 32770) ? TEST_PASS : TEST_FAIL;
}

TestResult_t test_BLE_advertising(void) {
    /* Verify BLE radio works by checking if test scanner detects advertisement */
    startAdvertising();
    /* Factory test scanner on PC confirms it sees the device */
    /* Pass signal via UART from test jig */
    uint32_t deadline = millis() + 5000;
    while (millis() < deadline) {
        if (UART_readByte() == TEST_ACK) return TEST_PASS;
    }
    return TEST_FAIL;
}

static const Test_t tests[] = {
    {"Crystal",        test_crystal,        2000},
    {"Flash R/W",      test_flashReadWrite, 3000},
    {"BLE Advertising",test_BLE_advertising, 5000},
    {"OTA Bootloader", test_otaBootloader,  10000},
    {"Power (sleep)",  test_sleepCurrent,  15000},
};

/* Run all tests, report via UART */
void ProductionTest_run(void) {
    bool allPassed = true;
    for (int i = 0; i < ARRAY_SIZE(tests); i++) {
        UART_printf("TEST[%d] %s... ", i, tests[i].name);
        TestResult_t r = tests[i].run();
        UART_printf("%s\r\n", r == TEST_PASS ? "PASS" : "FAIL");
        if (r == TEST_FAIL) allPassed = false;
    }
    UART_printf("RESULT: %s\r\n", allPassed ? "PASS" : "FAIL");
}
```

---

# PART 11: KEY PROJECTS DEEP DIVE

## 11.1 BLE Smart Meter (OES8800-211) — Architecture

### Full System Architecture

```
┌──────────────────────────────────────────────────────────┐
│                    Smart Meter Node                       │
│                                                          │
│  ┌─────────────┐    UART/RS-485    ┌──────────────────┐ │
│  │ Energy      │◄─────────────────►│  CC2340R5        │ │
│  │ Measurement │  DLMS/COSEM frames│                   │ │
│  │ IC (ADE9000)│                   │  BLE 5.3 Stack   │ │
│  └─────────────┘                   │  - GAP Central/  │ │
│                                    │    Peripheral     │ │
│  ┌─────────────┐    I2C           │  - GATT Server   │ │
│  │ RTC (DS3231)│◄─────────────────│  - SMP Security  │ │
│  └─────────────┘                   │  - OTA Bootloader│ │
│                                    │                   │ │
│  ┌─────────────┐    Flash SPI     │  FreeRTOS Tasks: │ │
│  │ W25Q32      │◄─────────────────│  - BLE Task      │ │
│  │ External    │  OTA storage     │  - DLMS Task     │ │
│  │ Flash       │                   │  - Sensor Task   │ │
│  └─────────────┘                   │  - OTA Task      │ │
│                                    └──────────────────┘ │
│            CR2032 coin cell (225 mAh)                    │
└──────────────────────────────────────────────────────────┘
            ↕ BLE 5.3 (1M PHY / Coded PHY)
┌──────────────────────────────────────────────────────────┐
│              BLE Gateway (CC2340R5 Central)               │
│              200m range, mesh-like topology               │
└──────────────────────────────────────────────────────────┘
            ↕ MQTT / Modbus
┌──────────────────────────────────────────────────────────┐
│                  AMI Head-End Server                      │
└──────────────────────────────────────────────────────────┘
```

## 11.2 WooshAir — AWS IoT Integration

### AWS IoT Architecture

```
ESP32-C3 Device
    │
    │ MQTT over TLS (port 8883)
    ↓
AWS IoT Core (message broker)
    │
    ├── IoT Rules Engine → Lambda → DynamoDB (store readings)
    │
    ├── Device Shadow (configuration sync)
    │   └── {"state": {"desired": {"aqi_threshold": 150},
    │                  "reported": {"aqi_threshold": 100}}}
    │
    └── AWS Greengrass (edge computing option)

/* Device Shadow for remote config (< 1s latency you achieved) */
/* Subscribe to delta topic: $aws/things/{thingName}/shadow/update/delta */
/* When cloud changes threshold, delta arrives in <1s via MQTT */
```

### MQTT Subscription Handler

```c
/* AWS IoT MQTT handler in ESP32-C3 firmware */
static void mqtt_event_handler(esp_mqtt_event_handle_t event) {
    switch (event->event_id) {
        case MQTT_EVENT_DATA:
            /* Parse topic */
            if (strncmp(event->topic,
                        "$aws/things/" THING_NAME "/shadow/update/delta",
                        event->topic_len) == 0) {
                /* Parse JSON delta */
                cJSON *root = cJSON_ParseWithLength(event->data, event->data_len);
                cJSON *state = cJSON_GetObjectItem(root, "state");
                cJSON *threshold = cJSON_GetObjectItem(state, "aqi_threshold");
                if (threshold) {
                    aqiThreshold = threshold->valueint;
                    /* Report back to shadow */
                    char reported[128];
                    snprintf(reported, sizeof(reported),
                             "{\"state\":{\"reported\":{\"aqi_threshold\":%d}}}",
                             aqiThreshold);
                    esp_mqtt_client_publish(client,
                        "$aws/things/" THING_NAME "/shadow/update",
                        reported, 0, 1, 0);
                }
                cJSON_Delete(root);
            }
            break;
    }
}
```

---

# PART 12: INTERVIEW MASTER Q&A

## Top 20 Interview Questions You Will Be Asked

**Q1: Walk me through the complete path of a BLE notification from your firmware to an Android app.**

*"Starting from the application: The sensor task reads power data and places it in a queue. The BLE task dequeues it and calls GATT_Notification() with the characteristic value handle and data. The GATT layer builds an ATT_HANDLE_VALUE_NTF PDU. L2CAP frames it with CID 0x0004 and fragments if necessary. The Link Layer schedules it into the next connection event, applies whitening, computes the CRC, and hands the packet to the radio. The radio transmits on the scheduled channel after frequency hopping to the correct channel per CSA #2. On the Android side, the BLE controller receives the packet, verifies the CRC and access address, strips the LL header, passes it up to L2CAP for reassembly, ATT parses the notification, GATT calls the registered callback, and finally the Android app's onCharacteristicChanged() fires."*

**Q2: You mention 99.8% delivery rate. How did you measure and achieve this?**

*"I measured it in the field by adding a sequence number to every DLMS frame delivered over BLE. The gateway tracked received sequence numbers and flagged gaps. Over 500 units × 30 days × 96 reads/day ≈ 1.44 billion delivery attempts, we had less than 0.2% failures. Achieving this required: AFH to avoid Wi-Fi channels in residential environments, connection parameter tuning (supervision timeout long enough to survive brief interference bursts), a retry mechanism at the application layer for missed DLMS readings, and PHY selection — switching to 1M PHY in noisy environments rather than forcing 2M PHY."*

**Q3: Explain how secure boot works in your bootloader.**

*"Secure boot is a chain of trust. In my implementation: The bootloader itself is stored in a protected flash region that's locked after production programming — it cannot be overwritten via OTA. The bootloader holds a public key (hard-coded in flash) and verifies a digital signature appended to every OTA image. The OTA server signs images with the corresponding private key using ECDSA-P256. At boot, the bootloader computes SHA-256 of the firmware, then verifies the ECDSA signature. If the signature check fails, the bootloader refuses to run that image and either rolls back to the previous image or enters a recovery mode. This prevents running unsigned or tampered firmware even if an attacker gains OTA access."*

**Q4: What is the difference between bare-metal and RTOS? When do you use each?**

*"Bare-metal is a super loop — while(1) — with interrupt handlers. Suitable for simple, single-task systems where you control timing precisely. RTOS is multiple concurrent tasks with a scheduler, synchronization primitives, and time management. I use bare-metal when: timing is critical (µs-level PWM, bit-banging), RAM is extremely limited (<4KB), or the application is truly single-threaded. I use RTOS (FreeRTOS) when: multiple independent operations run concurrently (BLE stack + sensor reading + DLMS protocol), blocking operations are needed without busy-waiting, or priorities need to be managed. In the smart meter, the BLE stack, DLMS parser, and OTA manager are all independent tasks in FreeRTOS — trying to manage their interactions in a bare-metal super loop would be a nightmare."*

**Q5: Describe how you would debug a BLE connection drop in the field.**

*"Systematic approach: First, I add logging at the GAP callback level — log the disconnect reason code (0x08=supervision timeout, 0x13=remote user terminated, 0x16=connection terminated by local host). The reason code tells me who disconnected and why. If supervision timeout: check if connection interval × (1+latency) × 2 < supervision timeout. If remote terminated: check if the phone app has a timeout. Next, I deploy a Wireshark capture using nRF Sniffer or Ellisys in the field environment to see if there are LL NACKs (retransmissions) due to RF interference. I check RSSI in the connection callback — values below -90dBm indicate marginal signal. I also check if the issue correlates with Wi-Fi activity by looking at the time-of-day pattern. Finally, I look at the AFH channel map reports to see if BLE is being pushed to fewer channels, indicating the blocked channels are spreading."*

---

# VOCABULARY BUILDER — TECHNICAL ENGLISH FOR INTERVIEWS

## Power Words for Technical Explanations

| Weak Phrase | Strong Alternative |
|---|---|
| "It does X" | "It is responsible for X" / "It handles X" |
| "I fixed a bug" | "I diagnosed and resolved a critical [issue type]" |
| "I made it faster" | "I optimized the [component], reducing [metric] by [amount]" |
| "I worked on" | "I architected / implemented / led / designed" |
| "It's a problem when" | "The failure mode occurs when" |
| "I think" | "Based on my analysis / From a technical standpoint" |
| "It didn't work" | "The root cause was..." |

## Phrases for Explaining Complex Concepts

- *"To put it simply..."* — before simplifying a complex concept
- *"The underlying mechanism is..."* — going deeper
- *"The trade-off here is..."* — showing engineering judgment
- *"In practice, this means..."* — connecting theory to reality
- *"The key insight is..."* — highlighting what matters
- *"What this enables is..."* — result-oriented thinking
- *"The failure mode would be..."* — showing you think about edge cases

---

*End of Study Guide — Version 1.0*
*Total estimated study time: 12–15 hours*
*Recommended: 2 sections per day, practice Q&A out loud*
