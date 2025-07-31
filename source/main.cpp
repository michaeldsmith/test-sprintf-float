#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <string>


struct commandline_args_t
{
  int numerator;
  int denominator;
  bool is_use_numerator_and_denominator;

  float float_value;
  bool is_use_float_value;

  bool is_use_preset_float_equation;

  int number_of_digits;

  std::string expected_string;

  commandline_args_t() :
    numerator(0),
    denominator(0),
    is_use_numerator_and_denominator(false),
    float_value(0.0f),
    is_use_float_value(false),
    is_use_preset_float_equation(false),
    number_of_digits(0),
    expected_string()
  {
    return;
  }
};

void print_argument_list(int argc, char* argv[])
{
  fprintf(stderr, "argument list:\n");
  for (int i = 0; i < argc; i++)
    fprintf(stderr, "\t argv[%d] = %s\n", i, argv[i]);
  return;
}

void print_usage(int argc, char* argv[])
{
  fprintf(stderr, "USAGE: %s \n", argv[0]);
  fprintf(stderr, "\nREQUIRED ARGUMENTS:\n");
  fprintf(stderr, " -expected_string  <string> -  expected string\n");
  fprintf(stderr, " -digits <number_of_digits> - number of digits of precision to print\n");
  fprintf(stderr, " -numerator <numerator> - numerator of rational input\n");
  fprintf(stderr, " -denominator <denominator> - denominator of rational input\n");
  fprintf(stderr, " -float <float> - floating point input\n");
  fprintf(stderr, " -use_preset_float_equation - use internal value equal to 3.0 * (1.2 - -0.2)/256.0 \n");

  fprintf(stderr, "\nUSAGE EXAMPLE: %s -numerator 1 -denominator 3 -num_digits 3 -expected_string 0.333\n", argv[0]);
  fprintf(stderr, "\nUSAGE EXAMPLE: %s -float 0.33333333 -num_digits 3 -expected_string 0.333\n", argv[0]);

  if (argc != 1)
  {
    fprintf(stderr, "\n");
    print_argument_list(argc, argv);
  }

  return;
}

int process_commandline_args(int argc, char* argv[], commandline_args_t* args)
{
  bool is_numerator_parsed = false;
  bool is_denominator_parsed = false;
  bool is_float_parsed = false;
  bool is_digits_parsed = false;
  bool is_expected_string_parsed = false;
  bool is_use_preset_float_equation_parsed = false;

  if (argc == 1)
  {
    return -1;
  }

  for (int i = 1; i < argc; i++)
  {
    int args_remaining = argc - i;

    // usage
    if (strcmp(argv[i], "-u") == 0)
    {
      print_usage(argc, argv);
      exit(1);
    }

    // numerator
    else if (strcmp(argv[i], "-numerator") == 0)
    {
      if (true == is_numerator_parsed)
      {
        fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -numerator is used twice, it may only be used once\n", __FUNCTION__, __FILE__, __LINE__);
        return -1;
      }

      if (args_remaining <= 1)
      {
        fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -numerator filename argument\n", __FUNCTION__, __FILE__, __LINE__);
        return -1;
      }
      else
      {
        args->numerator = atoi(argv[i + 1]);
        i = i + 1;
        is_numerator_parsed = true;
      }
    }

    // denominator
    else if (strcmp(argv[i], "-denominator") == 0)
    {
      if (true == is_denominator_parsed)
      {
        fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -denominator is used twice, it may only be used once\n", __FUNCTION__, __FILE__, __LINE__);
        return -1;
      }

      if (args_remaining <= 1)
      {
        fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -denominator filename argument\n", __FUNCTION__, __FILE__, __LINE__);
        return -1;
      }
      else
      {
        args->denominator = atoi(argv[i + 1]);
        i = i + 1;
        is_denominator_parsed = true;
        args->is_use_numerator_and_denominator = true;
      }
    }

    // float_value
    else if (strcmp(argv[i], "-float") == 0)
    {
      if (true == is_float_parsed)
      {
        fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -float is used twice, it may only be used once\n", __FUNCTION__, __FILE__, __LINE__);
        return -1;
      }

      if (args_remaining <= 1)
      {
        fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -float missing argument\n", __FUNCTION__, __FILE__, __LINE__);
        return -1;
      }
      else
      {
        args->float_value = (float)atof(argv[i + 1]);
        i = i + 1;
        is_float_parsed = true;
        args->is_use_float_value = true;
      }
    }

    // is_use_preset_float_equation
    else if (strcmp(argv[i], "-use_preset_float_equation") == 0)
    {
      if (true == is_use_preset_float_equation_parsed)
      {
        fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -use_preset_float_equation is used twice, it may only be used once\n", __FUNCTION__, __FILE__, __LINE__);
        return -1;
      }

      is_use_preset_float_equation_parsed = true;
      args->is_use_preset_float_equation = true;

    }

    // num_digits
    else if (strcmp(argv[i], "-digits") == 0)
    {
      if (true == is_digits_parsed)
      {
        fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -digits is used twice, it may only be used once\n", __FUNCTION__, __FILE__, __LINE__);
        return -1;
      }

      if (args_remaining <= 1)
      {
        fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -digits missing argument\n", __FUNCTION__, __FILE__, __LINE__);
        return -1;
      }
      else
      {
        args->number_of_digits = atoi(argv[i + 1]);
        i = i + 1;
        is_digits_parsed = true;
      }
    }

    // expected_string
    else if (strcmp(argv[i], "-expected_string") == 0)
    {
      if (true == is_expected_string_parsed)
      {
        fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -expected_string is used twice, it may only be used once\n", __FUNCTION__, __FILE__, __LINE__);
        return -1;
      }

      if (args_remaining <= 1)
      {
        fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -expected_string missing argument\n", __FUNCTION__, __FILE__, __LINE__);
        return -1;
      }
      else
      {
        args->expected_string = argv[i + 1];
        i = i + 1;
        is_expected_string_parsed = true;
      }
    }


    // unrecognized arguments
    else
    {
      fprintf(stderr, "COMMANDLINE PROCESSING ERROR: argv[%d] = %s, this is an unrecognized command-line argument\n", i, argv[i]);
      exit(-1);
    }
  } // end of argv[] processing loop

  // check that -numerator and -denominator are used together
  if (is_numerator_parsed != is_denominator_parsed)
  {
    if (is_numerator_parsed)
    {
      fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -numerator has been used but -denominator has not, -numerator must be used with -denominator\n", __FUNCTION__, __FILE__, __LINE__);
    }
    if (is_denominator_parsed)
    {
      fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -denominator has been used but -numerator has not, -numerator must be used with -denominator\n", __FUNCTION__, __FILE__, __LINE__);
    }
    
    return -1;
  }

  // check that -numerator and -denominator are not used with -float
  if (true == is_numerator_parsed && true == is_float_parsed )
  {
    fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -numerator and -denominator cannot be used with -float\n", __FUNCTION__, __FILE__, __LINE__);

    return -1;
  }

  // check that -numerator and -denominator are not used with -float
  if (true == is_numerator_parsed && true == is_use_preset_float_equation_parsed)
  {
    fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -numerator and -denominator cannot be used with -is_use_preset_float_equation_parsed\n", __FUNCTION__, __FILE__, __LINE__);

    return -1;
  }

  // check that -numerator and -denominator are not used with -float
  if (true == is_float_parsed && true == is_use_preset_float_equation_parsed)
  {
    fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -float cannot be used with -is_use_preset_float_equation_parsed\n", __FUNCTION__, __FILE__, __LINE__);

    return -1;
  }

  if (false == is_numerator_parsed && false == is_float_parsed && false == is_use_preset_float_equation_parsed)
  {
    fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n either (-numerator and -denominator) or must -float must be used or -use_preset_float_equation\n", __FUNCTION__, __FILE__, __LINE__);

    return -1;
  }

  if (true != is_digits_parsed)
  {
    fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -digits is missing but is a required argument\n", __FUNCTION__, __FILE__, __LINE__);
    return -1;
  }

  if (true != is_expected_string_parsed)
  {
    fprintf(stderr, "USAGE ERROR in function %s of file %s on line %d:\n -expected_string is missing but is a required argument\n", __FUNCTION__, __FILE__, __LINE__);
    return -1;
  }

  return 0;
}


int main(int argc, char* argv[])
{
  // process command line arguments
  commandline_args_t args;
  int process_command_args_ok = process_commandline_args(argc, argv, &args);
  if (process_command_args_ok != 0)
  {
    fprintf(stderr, "\n");
    print_argument_list(argc, argv);
    fprintf(stderr, "\n");
    fprintf(stderr, "use -u argument to print usage info\n");
    exit(1);
  }

  float float_value = 0.0f;
  if (true == args.is_use_float_value)
  {
    float_value = args.float_value;
  }
  else if (true == args.is_use_numerator_and_denominator)
  {
    float_value = (float)args.numerator / (float)args.denominator;
  }
  else if (true == args.is_use_preset_float_equation)
  {
    float_value = 3.0f * (1.2f - (-0.2f)) / 126.0f;
  }

  char sprintf_value[1024] = { '\0' };
  switch (args.number_of_digits)
  {
  case 0:
    sprintf(sprintf_value, "%.0f", float_value);
    break;
  case 1:
    sprintf(sprintf_value, "%.1f", float_value);
    break;
  case 2:
    sprintf(sprintf_value, "%.2f", float_value);
    break;
  case 3:
    sprintf(sprintf_value, "%.3f", float_value);
    break;
  case 4:
    sprintf(sprintf_value, "%.4f", float_value);
    break;
  case 5:
    sprintf(sprintf_value, "%.5f", float_value);
    break;
  case 6:
    sprintf(sprintf_value, "%.6f", float_value);
    break;
  case 7:
    sprintf(sprintf_value, "%.7f", float_value);
    break;
  case 8:
    sprintf(sprintf_value, "%.8f", float_value);
    break;
  case 9:
    sprintf(sprintf_value, "%.9f", float_value);
    break;
  case 10:
    sprintf(sprintf_value, "%.10f", float_value);
    break;
  case 11:
    sprintf(sprintf_value, "%.11f", float_value);
    break;
  case 12:
    sprintf(sprintf_value, "%.12f", float_value);
    break;


  default:
    {
      fprintf(stderr, "args.number_of_digits = %d is not supported\n", args.number_of_digits);
      return -1;
    }
  }
  

  bool is_strings_match = false;
  if (0 == strcmp(sprintf_value, args.expected_string.c_str() ) )
  {
    fprintf(stderr, "strings match:\n");
    fprintf(stderr, "expected_string = %s\n", args.expected_string.c_str());
    fprintf(stderr, "sprintf_value   = %s\n", sprintf_value);
    is_strings_match = true;
  }
  else
  {
    fprintf(stderr, "strings don't match:\n");
    fprintf(stderr, "expected_string = %s\n", args.expected_string.c_str() );
    fprintf(stderr, "sprintf_value   = %s\n", sprintf_value);
    is_strings_match = false;
  }

  return is_strings_match ? 0 : -1;
}
