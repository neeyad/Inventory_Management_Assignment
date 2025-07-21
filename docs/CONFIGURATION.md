# Configuration

## Environment Variables
- `ECOM_BRANDS`: Comma-separated list of allowed brands
- `ECOM_COLORS`: Comma-separated list of allowed colors
- `ECOM_SIZES`: Comma-separated list of allowed sizes
- `ECOM_DEFAULT_IMAGE_URL`: Default image URL for SKUs/products

## Data Files
- `/data/categories.json`
- `/data/products.json`
- `/data/skus.json`

## Logs
- `/logs/audit.log` (rotated, retained for 30 days)

## Backup/Restore
- Use handler methods to backup/restore data files
