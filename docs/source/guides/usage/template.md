# Template Integration

When depending on Robodash, it is recommended that you follow these instructions
for better user ease of use.

- **Do not bundle Robodash with your template** - It is not recommended that you
  add Robodash's source files to your template and distribute it with your own
  template. This prevents users from upgrading unless your own template
  upgrades, and places the burden on you to upgrade your template when Robodash
  upgrades. For new users, it is recommended instead to have a "starter project"
  that is pre-configured with Robodash and your own template.

- **Inform users that your template uses Robodash** - You should inform users
  that your template depends on Robodash so they know to install it.
  Additionally, provide some form of guidance for installing Robodash (a link to
  these docs or your own instructions). You should also indicate which version
  of Robodash your template uses, so users know what versions they can use.

- **Do not modify Robodash** - No modifications should be made to Robodash's
  header or source files, and no additions should be made to its namespace.
