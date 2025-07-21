# Audit Logging

- All create, update, delete, backup, and restore operations are logged.
- Log format: `timestamp | user | entity | operation`
- Logs stored in `/logs/audit.log` and rotated (retention: 30 days)
- Automatic cleanup of old logs
