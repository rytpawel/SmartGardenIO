Import("env")

from pathlib import Path


project_dir = Path(env.subst("$PROJECT_DIR"))
env_file = project_dir / ".env"


def load_env(path):
    if not path.exists():
        raise RuntimeError(
            "Missing .env file. Copy .env-template to .env."
        )

    variables = {}

    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.strip()

        if not line or line.startswith("#"):
            continue

        if "=" not in line:
            continue

        key, value = line.split("=", 1)

        variables[key.strip()] = value.strip()

    return variables


variables = load_env(env_file)

for key, value in variables.items():
    env.Append(
        CPPDEFINES=[
            (key, env.StringifyMacro(value))
        ]
    )

print(f"Environment configuration loaded ({len(variables)} variables).")