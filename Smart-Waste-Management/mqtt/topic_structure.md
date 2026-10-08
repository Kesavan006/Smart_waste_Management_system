# MQTT Topic Structure

## Main topic

```text
smartbin/bin001/data
```

## JSON payload

```json
{
  "bin_id": "BIN001",
  "distance": 12.5,
  "fill": 58,
  "status": "MEDIUM"
}
```

## Fields

| Field | Meaning |
|---|---|
| `bin_id` | Unique bin identifier |
| `distance` | Measured distance in cm |
| `fill` | Calculated fill percentage |
| `status` | LOW / MEDIUM / FULL |
