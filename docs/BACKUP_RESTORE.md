# Backup & Restore

## Backup
- Use handler `backup(path)` method to create a backup of data files.
- Example: `CategoryHandler::backup("data/categories.bak")`

## Restore
- Use handler `restore(path)` method to restore from backup.
- Example: `CategoryHandler::restore("data/categories.bak")`

## Data Files
- `/data/categories.json`
- `/data/products.json`
- `/data/skus.json`
