"""
This script is used to fetch open, cloded and merged PRS
and display them in tabular format
"""
import sys
import argparse
import json
import requests


def print_pulls_summery(result):
    """
    Function to print summery in tabular format.
    """
    # Table headers
    print_header_pr_number = "PR Number"
    print_header_title = "Title"
    print_header_created_date = "Created Date"
    print_header_last_updated = "Last Updated"
    print_header_author = "Author"
    print_header_assignee = "Assignee"

    # To print -- before header and after header using same indent size so
    # dashes will form line before and after.
    print_header_pr_number_dash = '----------'
    print_header_title_dash = "-----------------------------------------------"\
    + "---------------------------------------------------------------"
    print_header_created_date_dash = "--------------------"
    print_header_last_updated_dash = "--------------------"
    print_header_author_dash = "---------------"
    print_header_assignee_dash = "---------------"

    # Print '-----' before printing table headers
    print(f'{print_header_pr_number_dash:<10}| {print_header_title_dash:<110}|'
          f'{print_header_created_date_dash:<20}|'
          f'{print_header_last_updated_dash:<20}|'
          f'{print_header_author_dash:<15}|' 
          f'{print_header_assignee_dash:<15} |')

    # Print table headers
    print(f'{print_header_pr_number:<10}| {print_header_title:<110}|'
          f'{print_header_created_date:<20}|'
          f'{print_header_last_updated:<20}|'
          f'{print_header_author:<15}|'
          f'{print_header_assignee:<15} |')

    # Print '-----' After printing table headers
    print(f'{print_header_pr_number_dash:<10}| {print_header_title_dash:<110}|'
          f'{print_header_created_date_dash:<20}|'
          f'{print_header_last_updated_dash:<20}|'
          f'{print_header_author_dash:<15}|' 
          f'{print_header_assignee_dash:<15} |')

    # Iterate through each and ever PR item and print required details.
    for pull in result['items']:
        assignee = "None"
        # Most of the PRs dont have assignee if it has then value will be
        # stored as `assignee` else assigne is None
        if pull['assignee']:
            assignee = pull['assignee']['login']

        print(f"{pull['number']: <10}| {pull['title']: <110}|"
              f"{pull['created_at']: <20}|{pull['updated_at']: <20}|"
              f"{pull['user']['login']: <15}| {assignee: <15}|")

    # Print '-----' After printing table
    print(f'{print_header_pr_number_dash:<10}| {print_header_title_dash:<110}|'
          f'{print_header_created_date_dash:<20}|'
          f'{print_header_last_updated_dash:<20}|'
          f'{print_header_author_dash:<15}|' 
          f'{print_header_assignee_dash:<15} |')

def fetch_pulls(endpoint, schema, user_name, repo_name, branch, status,
                auth_token):
    """
    Function to fetch PR list from provided endpoints 
    """
    # We are considering closed means closed but without merge. Hence we are
    # adding unemerged as one more filter.
    if status == 'closed':
        url = schema + "://" + endpoint + "/search/issues?q=repo:" +\
        user_name + "/" + repo_name + "+is:pr+is:" + status +\
        "+is:unmerged+base:"+branch
    else:
        url = schema + "://" + endpoint + "/search/issues?q=repo:" +\
            user_name + "/" + repo_name + "+is:pr+is:" + status +\
                "+base:"+ branch 

    headers = {'Accept': 'application/vnd.github.text-match+json'}

    if auth_token:
        headers['Authorization'] = 'Bearer ' + auth_token

    try:
        response = requests.request("GET", url, headers=headers, timeout=30)
    except ConnectionError as err:
        print("Exception occured while calling api")
        print(err)
        sys.exit(2)

    # if response code is not 200. Exit.
    if response.status_code != 200:
        print("API call failed. Response code is:" + str(response.status_code) 
              + " "
              + response.text)
        sys.exit(2)

    response = json.loads(response.text)
    return response


def accept_inputs():
    """
        Function to accept intput and parse as per provided options.
    """
    parser = argparse.ArgumentParser(description='Print PR Summery')
    parser.add_argument('--endpoint', '-e', help='Git hub api endpoint',
                        default="api.github.com")
    parser.add_argument('--schema', '-s',  help='api schema HTTPS/HTTP',
                        default='https')
    parser.add_argument('--user-name', '-u', help='User name', required=True)
    parser.add_argument('--repo-name', '-r', help='Name of the repository',
                        required=True)
    parser.add_argument('--branch', '-b', help='Branch name', default='master')
    parser.add_argument('--auth_token', '-a', help='Auth Token')

    args = parser.parse_args()
    return args


def main():
    """
        Main function
    """
    args = accept_inputs()

    # Printing line of stars for Open Prs section
    print("************************************************ Open PRs *********"
         + "******************************************************************"
         +"**************************************\n")
    response = fetch_pulls(endpoint=args.endpoint,schema=args.schema,
                           user_name=args.user_name, repo_name=args.repo_name,
                           branch=args.branch,status='open',
                           auth_token=args.auth_token)
    print_pulls_summery(response)

    # Printing line of stars for Merged Prs section
    print("\n************************************************ Merged PRs *****"
          + "*****************************************************************"
          + "*******************************************\n")
    response = fetch_pulls(endpoint=args.endpoint,schema=args.schema,
                           user_name=args.user_name, repo_name=args.repo_name,
                           branch=args.branch,status='merged',
                           auth_token=args.auth_token)

    print_pulls_summery(response)

    # Printing line of stars for Closed Prs section
    print("\n************************************************ Closed PRs *****"
          +"******************************************************************"
          +"***************************************\n")

    response = fetch_pulls(endpoint=args.endpoint,schema=args.schema,
                           user_name=args.user_name, repo_name=args.repo_name,
                           branch=args.branch,status='closed',
                           auth_token=args.auth_token)

    print_pulls_summery(response)


if __name__ == '__main__':
    main()
